#include "ft_ssl.h"

static void	padd_with_msg_size(t_md5 *data, uint64_t *n)
{
	int		i;
	int		addr;

	i = 0;
	addr = data->padded_msg_len - MD5_MSG_LEN_BYTES;
	while (i < (MD5_MSG_LEN_BYTES))
	{
		/* ft_printf("---------\ni = %d\n", i); //DEBUG */
		/* ft_printf("n_nb_bytes - 1 - i = %d\n", n_nb_bytes - 1 - i); //DEBUG */
		data->padded_msg[addr] = ((t_byte *)n)[i];
		i++;
		addr++;
	}
}

t_ex_ret	message_padding_md5(t_md5 *data)
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
	return ((uint32_t)floor(abs_double(sin(i + 1)) * POW_2_32));
}

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

static void		fill_constants(int start, t_md5 *data,
						uint32_t (*func)(uint32_t b, uint32_t c, uint32_t d))
{
	int				i;
	uint32_t		shift[4];

	shift[0] = data->cst[start].shift;
	shift[1] = data->cst[start + 1].shift;
	shift[2] = data->cst[start + 2].shift;
	shift[3] = data->cst[start + 3].shift;
	i = start;
	while (i <= (start + 15))
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

void		fill_algo_constants_md5(t_md5 *data)
{
	data->cst[0].shift = 7;
	data->cst[1].shift = 12;
	data->cst[2].shift = 17;
	data->cst[3].shift = 22;
	fill_constants(0, data, &f_function);
	data->cst[16].shift = 5;
	data->cst[17].shift = 9;
	data->cst[18].shift = 14;
	data->cst[19].shift = 20;
	fill_constants(16, data, &g_function);
	data->cst[32].shift = 4;
	data->cst[33].shift = 11;
	data->cst[34].shift = 16;
	data->cst[35].shift = 23;
	fill_constants(32, data, &h_function);
	data->cst[48].shift = 6;
	data->cst[49].shift = 10;
	data->cst[50].shift = 15;
	data->cst[51].shift = 21;
	fill_constants(48, data, &i_function);
}
