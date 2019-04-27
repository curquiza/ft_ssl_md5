#include "ft_ssl.h"

/*
** The 32 bits of the fractional parts of the cube roots of the
** 64 prime numbers
*/
uint32_t g_k_sha1[SHA1_CHUNK_BYTES] = {
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

static uint32_t	left_rotate(uint32_t x, uint32_t n)
{
	return ((x << n) | (x >> (32 - n)));
}

static void	rslt_init(t_sha1_incr *rslt)
{
	rslt->a = SHA1_A0_INIT;
	rslt->b = SHA1_B0_INIT;
	rslt->c = SHA1_C0_INIT;
	rslt->d = SHA1_D0_INIT;
	rslt->e = SHA1_E0_INIT;
}

static uint32_t	get_word(uint32_t words[SHA1_WORD_NB], uint32_t incr_word)
{
	return (left_rotate(words[incr_word - 3] ^ words[incr_word - 8]
		^ words[incr_word - 14] ^ words[incr_word - 16], 1));
}

static void	fill_words(uint32_t words[SHA1_WORD_NB], uint32_t i, t_hash *data)
{
	uint32_t	incr_msg;
	uint32_t	incr_word;

	incr_msg = i * SHA1_CHUNK_BYTES;
	incr_word = 0;
	while (incr_word < SHA1_WORD_NB_FROM_CHUNK)
	{
		words[incr_word] = ptr_to_uint32(data->padded_msg + incr_msg);
		incr_msg += sizeof(uint32_t);
		incr_word++;
	}
	while (incr_word < SHA1_WORD_NB)
	{
		words[incr_word] = get_word(words, incr_word);
		incr_word++;
	}
}

static void	run_one_chunk(uint32_t words[SHA1_WORD_NB], t_sha1_incr *rslt,
				t_sha1_const *cst)
{
	int				i;
	uint32_t		tmp;
	t_sha1_incr		var;

	var.a = rslt->a;
	var.b = rslt->b;
	var.c = rslt->c;
	var.d = rslt->d;
	var.e = rslt->e;
	i = -1;
	while (++i < SHA1_ROUNDS)
	{
		tmp = left_rotate(var.a, 5) + cst[i].func(var.b, var.c, var.d)
			+ var.e + cst[i].k + words[i];
		var.e = var.d;
		var.d = var.c;
		var.c = left_rotate(var.b, 30);
		var.b = var.a;
		var.a = tmp;
	}
	rslt->a += var.a;
	rslt->b += var.b;
	rslt->c += var.c;
	rslt->d += var.d;
	rslt->e += var.e;
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

static void	fill_digest(t_hash *data, t_sha1_incr *rslt)
{
	size_t	sizeof_uint32;

	if (!(data->digest = ft_memalloc(SHA1_DIGEST_BYTES)))
		exit_malloc_err_with_clean(data);
	sizeof_uint32 = sizeof(uint32_t);
	ft_memcpy_back(data->digest, &rslt->a, sizeof_uint32);
	ft_memcpy_back(data->digest + sizeof_uint32, &rslt->b, sizeof_uint32);
	ft_memcpy_back(data->digest + 2 * sizeof_uint32, &rslt->c, sizeof_uint32);
	ft_memcpy_back(data->digest + 3 * sizeof_uint32, &rslt->d, sizeof_uint32);
	ft_memcpy_back(data->digest + 4 * sizeof_uint32, &rslt->e, sizeof_uint32);
}

static void	run_sha1_algo(t_hash *data, t_sha1_const *cst)
{
	uint32_t	i;
	uint32_t	words[SHA1_WORD_NB];
	t_sha1_incr	rslt;

	rslt_init(&rslt);
	i = 0;
	while (i < (data->padded_msg_len / (SHA1_CHUNK_BYTES)))
	{
		fill_words(words, i, data);
		run_one_chunk(words, &rslt, cst);
		i++;
	}
	fill_digest(data, &rslt);
}

void	fill_sha1_digest(t_hash *data, int alt)
{
	(void)alt;
	t_sha1_const	cst[SHA1_WORD_NB];
	data->digest_len = SHA1_DIGEST_BYTES;
	message_padding_sha1(data);
	fill_algo_constants_sha1(cst);
	run_sha1_algo(data, cst);
}
