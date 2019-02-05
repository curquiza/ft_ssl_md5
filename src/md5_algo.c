#include "ft_ssl.h"

static uint32_t	left_rotate(uint32_t x, uint32_t n)
{
	/* ft_printf("x = %u, n = %u, left_rotate = %u\n", x, n, (x << n) | (x >> (32 - n))); //DEBUG */
	/* (x << n) | (x >> (32 - n)) */
	return ((x << n) | (x >> (32 - n)));
}

static void	run_one_chunk(uint32_t words[MD5_WORD_NB], t_md5_incr *rslt, t_md5_const *cst)
{
	int			i;
	uint32_t	f;
	t_md5_incr	var;

	var.a = rslt->a;
	var.b = rslt->b;
	var.c = rslt->c;
	var.d = rslt->d;
	i = 0;
	while (i < MD5_CHUNK_BYTES)
	{
		/* ft_printf("START i = %d \t A = %u, B = %u, C = %u, D = %u\n", i, var.a, var.b, var.c, var.d); //DEBUG */
		f = cst[i].func(var.b, var.c, var.d); 
		/* ft_printf("first step f = %u\n", f); //DEBUG */
		f += var.a + cst[i].radian + words[cst[i].word_index];
		/* ft_printf("words[%d] = %u\n", data->cst[i].word_index, words[data->cst[i].word_index]); //DEBUG */
		/* ft_printf("cst[%d].radian = %u\n", i, data->cst[i].radian); //DEBUG */
		/* ft_printf("second step f = %u\n", f); //DEBUG */
		var.a = var.d;
		var.d = var.c;
		var.c = var.b;
		var.b += left_rotate(f, cst[i].shift);
		/* ft_printf("third step f = %u\n", var.b); //DEBUG */
		/* ft_printf("END i = %d \t A = %u, B = %u, C = %u, D = %u\n", i, var.a, var.b, var.c, var.d); //DEBUG */
		i++;
	}
	rslt->a += var.a;
	rslt->b += var.b;
	rslt->c += var.c;
	rslt->d += var.d;
}

static void		fill_words(uint32_t words[MD5_WORD_NB], uint32_t i, t_hash *data)
{
	uint32_t	incr_msg;
	uint32_t	incr_word;

	incr_msg = i * MD5_CHUNK_BYTES;
	incr_word = 0;
	while (incr_word < MD5_WORD_NB)
	{
		words[incr_word] = ptr_to_uint32_swap(data->padded_msg + incr_msg);
		incr_msg += sizeof(uint32_t);
		/* printf("word_in_loop[%d] = %u = 0x%x\n", incr_word, words[incr_word], words[incr_word]); //DEBUG */
		incr_word++;
	}
}

static t_ex_ret	fill_digest(t_hash *data, t_md5_incr *rslt)
{
	size_t	sizeof_uint32;

	if (!(data->digest = ft_memalloc(MD5_DIGEST_BYTES)))
		return (FAILURE);
	sizeof_uint32 = sizeof(uint32_t);
	ft_memmove(data->digest, &rslt->a, sizeof_uint32);
	ft_memmove(data->digest + sizeof_uint32, &rslt->b, sizeof_uint32);
	ft_memmove(data->digest + 2 * sizeof_uint32, &rslt->c, sizeof_uint32);
	ft_memmove(data->digest + 3 * sizeof_uint32, &rslt->d, sizeof_uint32);
	return (SUCCESS);
}

static t_ex_ret	run_md5_algo(t_hash *data, t_md5_const *cst)
{
	uint32_t	i;
	uint32_t	words[MD5_WORD_NB];
	t_md5_incr		rslt;

	rslt.a = MD5_A0_INIT;
	rslt.b = MD5_B0_INIT;
	rslt.c = MD5_C0_INIT;
	rslt.d = MD5_D0_INIT;
	i = 0;
	while (i < (data->padded_msg_len / (MD5_CHUNK_BYTES)))
	{
		/* ft_printf("run one chunk !\n"); //DEBUG */
		fill_words(words, i, data);
		run_one_chunk(words, &rslt, cst);
		i++;
	}
	return (fill_digest(data, &rslt));
}

t_ex_ret	fill_md5_digest(t_hash *data)
{
	t_md5_const		cst[MD5_CHUNK_BYTES];
	/* ft_printf("message = \"%s\"\n", data->msg); // DEBUG */
	/* ft_printf("message bits = %d = 0x%x\n", data->msg_len * 8, 8 * data->msg_len); // DEBUG */
	data->digest_len = MD5_DIGEST_BYTES;
	if (message_padding_md5(data) == FAILURE)
		return (FAILURE);
	fill_algo_constants_md5(cst);
	return (run_md5_algo(data, cst));
}
