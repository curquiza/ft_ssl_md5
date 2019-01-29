#include "ft_ssl.h"

static void	padd_with_msg_size(t_md5 *data, uint64_t *n)
{
	int		i;
	int		addr;

	i = 0;
	addr = data->padded_msg_len - MSG_LEN_BYTES;
	while (i < (MSG_LEN_BYTES))
	{
		/* ft_printf("---------\ni = %d\n", i); //DEBUG */
		/* ft_printf("n_nb_bytes - 1 - i = %d\n", n_nb_bytes - 1 - i); //DEBUG */
		data->padded_msg[addr] = ((t_byte *)n)[i];
		i++;
		addr++;
	}
}

static t_ex_ret	message_padding(t_md5 *data)
{
	size_t		tmp_len;
	uint64_t	msg_len_bits;

	tmp_len = (data->msg_len + 1 + MSG_LEN_BYTES);
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
	/* hex_display(data->padded_msg, data->padded_msg_len); //DEBUG */
	return (SUCCESS);
}

static uint32_t	f_function(uint32_t b, uint32_t c, uint32_t d)
{
	/* ft_printf("b = %u\n", b); //DEBUG */
	/* ft_printf("c = %u\n", c); //DEBUG */
	/* ft_printf("d = %u\n", d); //DEBUG */
	/* printf("(b & c) | (~b & d)  = %u\n", (b & c) | (~b & d)); //DEBUG */
	return ((b & c) | ((~b) & d));
}

static uint32_t	g_function(uint32_t b, uint32_t c, uint32_t d)
{
	return ((b & d) | (c & ~d));
}

static uint32_t	h_function(uint32_t b, uint32_t c, uint32_t d)
{
	return (b ^ c ^ d);
}

static uint32_t	i_function(uint32_t b, uint32_t c, uint32_t d)
{
	return (c ^ (b | ~d));
}

static uint32_t		get_radian_const(int i)
{
	return ((uint32_t)floor(abs_double(sin(i + 1)) * POW_2_32)); // /!\ FLOOR & SIN;
}

// faire des fonctions pour chaque
// passer la fonction en arg
// pour avoir que 4 params => start seulement et end = start + 16
static int				get_word_index(int i)
{
	if (i < 16)
		return (i);
	else if (i < 32)
		return ((5 * i + 1) % 16);
	else if (i < 48)
		return ((3 * i + 5) % 16);
	else
		return ((7 * i) % 16);
}

static void		fill_constants(int start, int end, t_md5 *data, uint32_t (*func)(uint32_t b, uint32_t c, uint32_t d))
{
	int				i;
	uint32_t		shift[4];

	shift[0] = data->cst[start].shift;
	shift[1] = data->cst[start + 1].shift;
	shift[2] = data->cst[start + 2].shift;
	shift[3] = data->cst[start + 3].shift;
	i = start;
	while (i <= end)
	{
		/* ft_printf("i = %d\n", i); //DEBUG */
		data->cst[i].shift = shift[i % 4];
		/* ft_printf("cst[%d].shift = %d\n", i, data->cst[i].shift); //DEBUG */
		data->cst[i].radian = get_radian_const(i);
		/* ft_printf("cst[%d].sin = %u\n", i, data->cst[i].radian); //DEBUG */
		data->cst[i].func = func;
		data->cst[i].word_index = get_word_index(i);
		i++;
	}
}

static void		fill_algo_constants(t_md5 *data)
{
	data->cst[0].shift = 7;
	data->cst[1].shift = 12;
	data->cst[2].shift = 17;
	data->cst[3].shift = 22;
	fill_constants(0, 15, data, &f_function);
	data->cst[16].shift = 5;
	data->cst[17].shift = 9;
	data->cst[18].shift = 14;
	data->cst[19].shift = 20;
	fill_constants(16, 31, data, &g_function);
	data->cst[32].shift = 4;
	data->cst[33].shift = 11;
	data->cst[34].shift = 16;
	data->cst[35].shift = 23;
	fill_constants(32, 47, data, &h_function);
	data->cst[48].shift = 6;
	data->cst[49].shift = 10;
	data->cst[50].shift = 15;
	data->cst[51].shift = 21;
	fill_constants(48, 63, data, &i_function);
}

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
	/* t_byte		words[MD5_WORD_NB][MD5_WORD_LEN_BYTES]; */
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
	if (message_padding(data) == FAILURE)
		return (FAILURE);
	fill_algo_constants(data);
	run_md5_algo(data);
	return (SUCCESS);
}
