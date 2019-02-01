#include "ft_ssl.h"

static uint32_t	left_rotate(uint32_t x, uint32_t n)
{
	/* ft_printf("x = %u, n = %u, left_rotate = %u\n", x, n, (x << n) | (x >> (32 - n))); //DEBUG */
	/* (x << n) | (x >> (32 - n)) */
	return ((x << n) | (x >> (32 - n)));
}

static void	run_one_chunk(t_md5 *data, uint32_t words[MD5_WORD_NB])
{
	int			i;
	uint32_t	f;
	t_md5_incr	var;

	var.a = data->rslt.a;
	var.b = data->rslt.b;
	var.c = data->rslt.c;
	var.d = data->rslt.d;
	i = 0;
	while (i < MD5_CHUNK_BYTES)
	{
		/* ft_printf("START i = %d \t A = %u, B = %u, C = %u, D = %u\n", i, var.a, var.b, var.c, var.d); //DEBUG */
		f = data->cst[i].func(var.b, var.c, var.d); 
		/* ft_printf("first step f = %u\n", f); //DEBUG */
		f += var.a + data->cst[i].radian + words[data->cst[i].word_index];
		/* ft_printf("words[%d] = %u\n", data->cst[i].word_index, words[data->cst[i].word_index]); //DEBUG */
		/* ft_printf("cst[%d].radian = %u\n", i, data->cst[i].radian); //DEBUG */
		/* ft_printf("second step f = %u\n", f); //DEBUG */
		var.a = var.d;
		var.d = var.c;
		var.c = var.b;
		var.b += left_rotate(f, data->cst[i].shift);
		/* ft_printf("third step f = %u\n", var.b); //DEBUG */
		/* ft_printf("END i = %d \t A = %u, B = %u, C = %u, D = %u\n", i, var.a, var.b, var.c, var.d); //DEBUG */
		i++;
	}
	data->rslt.a += var.a;
	data->rslt.b += var.b;
	data->rslt.c += var.c;
	data->rslt.d += var.d;
}

static uint32_t	ptr_to_uint32_swap(t_byte *str)
{
	uint32_t		rslt;

	rslt = 0;
	rslt = (rslt | (t_byte)str[3]) << 8;
	rslt = (rslt | (t_byte)str[2]) << 8;
	rslt = (rslt | (t_byte)str[1]) << 8;
	rslt |= (t_byte)str[0];
	return (rslt);
}

static void		fill_words(uint32_t words[MD5_WORD_NB], uint32_t i, t_md5 *data)
{
	uint32_t	incr_msg;
	uint32_t	incr_word;

	incr_msg = i * MD5_CHUNK_BYTES;
	incr_word = 0;
	while (incr_word < MD5_WORD_NB)
	{
		words[incr_word] = ptr_to_uint32_swap(data->padded_msg + incr_msg);
		incr_msg += 4;
		/* printf("word_in_loop[%d] = %u = 0x%x\n", incr_word, words[incr_word], words[incr_word]); //DEBUG */
		incr_word++;
	}
}

static void	fill_digest(t_md5 *data)
{
	size_t	sizeof_uint32;

	sizeof_uint32 = sizeof(uint32_t);
	ft_memmove(data->digest, &data->rslt.a, sizeof_uint32);
	ft_memmove(data->digest + sizeof_uint32, &data->rslt.b, sizeof_uint32);
	ft_memmove(data->digest + 2 * sizeof_uint32, &data->rslt.c, sizeof_uint32);
	ft_memmove(data->digest + 3 * sizeof_uint32, &data->rslt.d, sizeof_uint32);
}

static void	run_md5_algo(t_md5 *data)
{
	uint32_t	i;
	uint32_t	words[MD5_WORD_NB];

	data->rslt.a = MD5_A0_INIT;
	data->rslt.b = MD5_B0_INIT;
	data->rslt.c = MD5_C0_INIT;
	data->rslt.d = MD5_D0_INIT;
	i = 0;
	while (i < (data->padded_msg_len / (MD5_CHUNK_BYTES)))
	{
		/* ft_printf("run one chunk !\n"); //DEBUG */
		fill_words(words, i, data);
		run_one_chunk(data, words);
		i++;
	}
	fill_digest(data);
}

t_ex_ret	fill_md5_digest(t_md5 *data)
{
	/* ft_printf("message = \"%s\"\n", data->msg); // DEBUG */
	/* ft_printf("message bits = %d = 0x%x\n", data->msg_len * 8, 8 * data->msg_len); // DEBUG */
	if (message_padding_md5(data) == FAILURE)
		return (FAILURE);
	fill_algo_constants_md5(data);
	run_md5_algo(data);
	return (SUCCESS);
}
