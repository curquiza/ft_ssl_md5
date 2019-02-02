#include "ft_ssl.h"

/*
** The 32 bits of the fractional parts of the cube roots of the
** 64 prime numbers
*/
uint32_t g_k_sha256[SHA256_CHUNK_BYTES] = {
	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1,
	0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
	0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174, 0xe49b69c1, 0xefbe4786,
	0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
	0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147,
	0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
	0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85, 0xa2bfe8a1, 0xa81a664b,
	0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
	0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a,
	0x5b9cca4f, 0x682e6ff3, 0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
	0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

// DEBUG
/* void		uint32_display(t_byte *s, size_t len) */
/* { */
/* 	size_t		i; */
/*  */
/* 	i = 0; */
/* 	while (i < len) */
/* 	{ */
/* 		ft_printf("%u ", (t_byte)s[i]); */
/* 		i++; */
/* 	} */
/* 	write(1, "\n", 1); */
/* } */

static void	padd_with_msg_size(t_sha256 *data, uint64_t *n)
{
	int		i;
	int		addr;

	i = SHA256_MSG_LEN_BYTES - 1;
	addr = data->padded_msg_len - SHA256_MSG_LEN_BYTES;
	while (i >= 0)
	{
		data->padded_msg[addr] = ((t_byte *)n)[i];
		i--;
		addr++;
	}
}

static t_ex_ret	message_padding_sha256(t_sha256 *data)
{
	size_t		tmp_len;
	uint64_t	msg_len_bits;

	tmp_len = (data->msg_len + 1 + MD5_MSG_LEN_BYTES);
	if (tmp_len % (MD5_CHUNK_BYTES) == 0)
		data->padded_msg_len = tmp_len;
	else
		data->padded_msg_len = (tmp_len / (MD5_CHUNK_BYTES) + 1)
					* (MD5_CHUNK_BYTES);
	if (!(data->padded_msg = (t_byte *)ft_memalloc(data->padded_msg_len)))
		return (FAILURE);
	/* ft_printf("padded_msg len = %d = 0x%x\n", data->padded_msg_len, data->padded_msg_len); //DEBUG */
	ft_memmove(data->padded_msg, data->msg, data->msg_len);
	data->padded_msg[data->msg_len] = (t_byte)(1 << 7);
	msg_len_bits = 8 * data->msg_len;
	padd_with_msg_size(data, &msg_len_bits);
	/* uint32_display(data->padded_msg, data->padded_msg_len); //DEBUG */
	return (SUCCESS);
}

static uint32_t	right_rotate(uint32_t x, uint32_t n)
{
	return ((x >> n) | (x << (32 - n)));
}

static uint32_t	right_shift(uint32_t x, uint32_t n)
{
	return (x >> n);
}

static void	rslt_init(t_sha256 *data)
{
	data->rslt.a = SHA256_A0_INIT;
	data->rslt.b = SHA256_B0_INIT;
	data->rslt.c = SHA256_C0_INIT;
	data->rslt.d = SHA256_D0_INIT;
	data->rslt.e = SHA256_E0_INIT;
	data->rslt.f = SHA256_F0_INIT;
	data->rslt.g = SHA256_G0_INIT;
	data->rslt.h = SHA256_H0_INIT;
}

static uint32_t	get_word(uint32_t words[SHA256_WORD_NB], uint32_t incr_word)
{
	uint32_t	s0;
	uint32_t	s1;

	s0 = (right_rotate(words[incr_word - 15], 7))
		^ (right_rotate(words[incr_word - 15], 18))
		^ (right_shift(words[incr_word - 15], 3));
	s1 = (right_rotate(words[incr_word - 2], 17))
		^ (right_rotate(words[incr_word - 2], 19))
		^ (right_shift(words[incr_word - 2], 10));
	return (words[incr_word - 16] + s0 + words[incr_word - 7] + s1);
}

static void	fill_words(uint32_t words[SHA256_WORD_NB], uint32_t i, t_sha256 *data)
{
	uint32_t	incr_msg;
	uint32_t	incr_word;

	incr_msg = i * SHA256_CHUNK_BYTES;
	incr_word = 0;
	while (incr_word < SHA256_WORD_NB_FROM_CHUNK)
	{
		words[incr_word] = ptr_to_uint32(data->padded_msg + incr_msg);
		incr_msg += sizeof(uint32_t);
		/* printf("word_in_loop[%d] = %u\n", incr_word, words[incr_word]); //DEBUG */
		incr_word++;
	}
	while (incr_word < SHA256_WORD_NB)
	{
		words[incr_word] = get_word(words, incr_word);
		/* printf("word_in_loop[%d] = %u\n", incr_word, words[incr_word]); //DEBUG */
		incr_word++;
	}
}

static void	fill_tmp_var(int i, t_sha256_incr *var, uint32_t words[SHA256_WORD_NB])
{
	uint32_t		s1;
	uint32_t		s0;
	uint32_t		ch;
	uint32_t		maj;
	uint32_t		temp1;
	uint32_t		temp2;


	s1 = right_rotate(var->e, 6) ^ right_rotate(var->e, 11) ^ right_rotate(var->e, 25);
	ch = (var->e & var->f) ^ (~var->e & var->g);
	temp1 = var->h + s1 + ch + g_k_sha256[i] + words[i];
	s0 = right_rotate(var->a, 2) ^ right_rotate(var->a, 13) ^ right_rotate(var->a, 22);
	maj = (var->a & var->b) ^ (var->a & var->c) ^ (var->b & var->c);
	temp2 = s0 + maj;
	var->h = var->g;
	var->g = var->f;
	var->f = var->e;
	var->e = var->d + temp1;
	var->d = var->c;
	var->c = var->b;
	var->b = var->a;
	var->a = temp1 + temp2;
}

static void	run_one_chunk(t_sha256 *data, uint32_t words[SHA256_WORD_NB])
{
	int				i;
	t_sha256_incr	var;

	var.a = data->rslt.a;
	var.b = data->rslt.b;
	var.c = data->rslt.c;
	var.d = data->rslt.d;
	var.e = data->rslt.e;
	var.f = data->rslt.f;
	var.g = data->rslt.g;
	var.h = data->rslt.h;
	i = 0;
	while (i < SHA256_CHUNK_BYTES)
	{
		fill_tmp_var(i, &var, words);
		i++;
	}
	data->rslt.a += var.a;
	data->rslt.b += var.b;
	data->rslt.c += var.c;
	data->rslt.d += var.d;
	data->rslt.e += var.e;
	data->rslt.f += var.f;
	data->rslt.g += var.g;
	data->rslt.h += var.h;
}

static void	*ft_memcpy_back(t_byte *dst, const void *src, size_t n)
{
	int				i;
	size_t			j;

	i = n - 1;
	j = 0;
	while (i >= 0)
	{
		dst[j] = ((t_byte *)src)[i];
		i--;
		j++;
	}
	return (dst);
}

static void	fill_digest(t_sha256 *data)
{
	size_t	sizeof_uint32;

	sizeof_uint32 = sizeof(uint32_t);
	ft_memcpy_back(data->digest, &data->rslt.a, sizeof_uint32);
	ft_memcpy_back(data->digest + sizeof_uint32, &data->rslt.b, sizeof_uint32);
	ft_memcpy_back(data->digest + 2 * sizeof_uint32, &data->rslt.c, sizeof_uint32);
	ft_memcpy_back(data->digest + 3 * sizeof_uint32, &data->rslt.d, sizeof_uint32);
	ft_memcpy_back(data->digest + 4 * sizeof_uint32, &data->rslt.e, sizeof_uint32);
	ft_memcpy_back(data->digest + 5 * sizeof_uint32, &data->rslt.f, sizeof_uint32);
	ft_memcpy_back(data->digest + 6 * sizeof_uint32, &data->rslt.g, sizeof_uint32);
	ft_memcpy_back(data->digest + 7 * sizeof_uint32, &data->rslt.h, sizeof_uint32);
}

static void	run_sha256_algo(t_sha256 *data)
{
	uint32_t	i;
	uint32_t	words[SHA256_WORD_NB];

	rslt_init(data);
	i = 0;
	while (i < (data->padded_msg_len / (SHA256_CHUNK_BYTES)))
	{
		/* ft_printf("run one chunk !\n"); //DEBUG */
		fill_words(words, i, data);
		run_one_chunk(data, words);
		i++;
	}
	fill_digest(data);
}

t_ex_ret	fill_sha256_digest(t_sha256 *data)
{
	/* ft_printf("message = \"%s\"\n", data->msg); // DEBUG */
	/* ft_printf("message bits = %d = 0x%x\n", data->msg_len * 8, 8 * data->msg_len); // DEBUG */
	if (message_padding_sha256(data) == FAILURE)
		return (FAILURE);
	run_sha256_algo(data);
	return (SUCCESS);
}
