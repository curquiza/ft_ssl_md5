#include "ft_ssl.h"

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


static void	padd_with_msg_size(t_hash *data, uint64_t *n)
{
	int		i;
	int		addr;

	i = SHA1_MSG_LEN_BYTES - 1;
	addr = data->padded_msg_len - SHA1_MSG_LEN_BYTES;
	while (i >= 0)
	{
		data->padded_msg[addr] = ((t_byte *)n)[i];
		i--;
		addr++;
	}
}

void	message_padding_sha1(t_hash *data)
{
	size_t		tmp_len;
	uint64_t	msg_len_bits;

	tmp_len = (data->msg_len + 1 + SHA1_MSG_LEN_BYTES);
	if (tmp_len % (SHA1_CHUNK_BYTES) == 0)
		data->padded_msg_len = tmp_len;
	else
		data->padded_msg_len = (tmp_len / (SHA1_CHUNK_BYTES) + 1)
					* (SHA1_CHUNK_BYTES);
	if (!(data->padded_msg = (t_byte *)ft_memalloc(data->padded_msg_len)))
		exit_malloc_err_with_clean(data);
	ft_memmove(data->padded_msg, data->msg, data->msg_len);
	data->padded_msg[data->msg_len] = (t_byte)(1 << 7);
	msg_len_bits = 8 * data->msg_len;
	padd_with_msg_size(data, &msg_len_bits);
	/* uint32_display(data->padded_msg, data->padded_msg_len); //DEBUG */
}

static uint32_t	f_function_0_19(uint32_t b, uint32_t c, uint32_t d)
{
	return ((b & c) | (~b & d));
}

static uint32_t	f_function_20_39(uint32_t b, uint32_t c, uint32_t d)
{
	return (b ^ c ^ d);
}

static uint32_t	f_function_40_59(uint32_t b, uint32_t c, uint32_t d)
{
	return ((b & c) | (b & d) | (c & d));
}

static uint32_t	f_function_60_79(uint32_t b, uint32_t c, uint32_t d)
{
	return (b ^ c ^ d);
}

static void		fill_constants(t_sha1_const *cst, int start, uint32_t k,
						uint32_t (*func)(uint32_t b, uint32_t c, uint32_t d))
{
	int		i;

	i = start;
	while (i < start + 20)
	{
		cst[i].k = k;
		cst[i].func = func;
		i++;
	}
}

void		fill_algo_constants_sha1(t_sha1_const *cst)
{
	fill_constants(cst, 0, 0x5a827999, &f_function_0_19);
	fill_constants(cst, 20, 0x6ed9eba1, &f_function_20_39);
	fill_constants(cst, 40, 0x8f1bbcdc, &f_function_40_59);
	fill_constants(cst, 60, 0xca62c1d6, &f_function_60_79);
}
