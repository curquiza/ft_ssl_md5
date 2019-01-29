#include "ft_ssl.h"

void		hex_display_details(t_byte *s, size_t len)
{
	size_t		i;

	i = 0;
	while (i < len)
	{
		if (i % 4 == 0)
			ft_printf("%03d - %03d\t", i, i + 3);
		ft_printf("%02x", (t_byte)s[i]);
		i++;
		if (i % 4 == 0)
			write(1, "\n", 1);
		else
			write(1, " ", 1);
	}
	write(1, "\n", 1);
}

void		hex_display(t_byte *s, size_t len)
{
	size_t		i;

	i = 0;
	while (i < len)
	{
		ft_printf("%02x", (t_byte)s[i]);
		i++;
	}
	write(1, "\n", 1);
}

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
	ft_printf("padded_msg len = %d = 0x%x\n", data->padded_msg_len, data->padded_msg_len); //DEBUG
	ft_memmove(data->padded_msg, data->msg, data->msg_len);
	data->padded_msg[data->msg_len] = (t_byte)(1 << 7);
	msg_len_bits = 8 * data->msg_len;
	padd_with_msg_size(data, &msg_len_bits);
	hex_display(data->padded_msg, data->padded_msg_len); //DEBUG
	return (SUCCESS);
}

uint32_t	f_function(uint32_t b, uint32_t c, uint32_t d)
{
	return ((b & c) | ((~b) & d));
}

uint32_t	g_function(uint32_t b, uint32_t c, uint32_t d)
{
	return ((b & c) | (c & (~d)));
}

uint32_t	h_function(uint32_t b, uint32_t c, uint32_t d)
{
	return (b ^ c ^ d);
}

uint32_t	i_function(uint32_t b, uint32_t c, uint32_t d)
{
	return (b ^ (c | (~d)));
}

uint32_t		get_radian_const(int i)
{
	return ((uint32_t)floor(abs_double(sin(i + 1)) * POW_2_32)); // /!\ FLOOR & SIN;
}

void		fill_constants(int start, int end, t_md5 *data, uint32_t (*func)(uint32_t b, uint32_t c, uint32_t d))
{
	int				i;
	uint32_t		shift[4];

	shift[0] = data->var[start].shift;
	shift[1] = data->var[start + 1].shift;
	shift[2] = data->var[start + 2].shift;
	shift[3] = data->var[start + 3].shift;
	i = start;
	while (i <= end)
	{
		ft_printf("i = %d\n", i); //DEBUG
		data->var[i].shift = shift[i % 4];
		ft_printf("shift = %d\n", data->var[i].shift); //DEBUG
		data->var[i].radian = get_radian_const(i);
		ft_printf("sin_const = 0x%x\n", data->var[i].radian); //DEBUG
		data->var[i].func = func;
		i++;
	}
}

void		fill_algo_constants(t_md5 *data)
{
	data->var[0].shift = 7;
	data->var[1].shift = 12;
	data->var[2].shift = 17;
	data->var[3].shift = 22;
	fill_constants(0, 15, data, &f_function);
	data->var[16].shift = 5;
	data->var[17].shift = 9;
	data->var[18].shift = 14;
	data->var[19].shift = 20;
	fill_constants(16, 31, data, &g_function);
	data->var[32].shift = 4;
	data->var[33].shift = 11;
	data->var[34].shift = 16;
	data->var[35].shift = 23;
	fill_constants(32, 47, data, &h_function);
	data->var[48].shift = 6;
	data->var[49].shift = 10;
	data->var[50].shift = 15;
	data->var[51].shift = 21;
	fill_constants(48, 63, data, &i_function);
}

t_ex_ret	run_one_chunk(t_md5 *data, t_byte words[MD5_WORD_NB][MD5_WORD_LEN_BYTES])
{
	t_md5_incr	tmp;

	(void)words;
	tmp.a = data->rslt.a;
	tmp.b = data->rslt.b;
	tmp.c = data->rslt.c;
	tmp.d = data->rslt.d;
	ft_printf("run one chunk !\n"); //DEBUG
	return (SUCCESS);
}

void		fill_words(t_byte words[MD5_WORD_NB][MD5_WORD_LEN_BYTES], uint32_t i, t_md5 *data)
{
	uint32_t	incr_msg;
	uint32_t	incr_word_nb;
	uint32_t	incr_word_len;

	ft_printf("Fill words ! i = %d\n", i); //DEBUG
	incr_msg = i * MD5_CHUNK_BYTES;
	incr_word_nb = 0;
	while (incr_word_nb < MD5_WORD_NB)
	{
		incr_word_len = 0;
		while (incr_word_len < MD5_WORD_LEN_BYTES)
		{
			words[incr_word_nb][incr_word_len] = data->padded_msg[incr_msg];
			incr_word_len++;
			incr_msg++;
		}
		incr_word_nb++;
	}
}

t_ex_ret	run_md5_algo(t_md5 *data)
{
	uint32_t	i;
	t_byte		words[MD5_WORD_NB][MD5_WORD_LEN_BYTES];

	data->rslt.a = MD5_A0_INIT;
	data->rslt.b = MD5_B0_INIT;
	data->rslt.c = MD5_C0_INIT;
	data->rslt.d = MD5_D0_INIT;
	i = 0;
	while (i < (data->padded_msg_len / (MD5_CHUNK_BYTES)))
	{
		fill_words(words, i, data);
		run_one_chunk(data, words);
		i++;
	}
	return (SUCCESS);
}

t_ex_ret	fill_md5_digest(t_md5 *data)
{
	ft_printf("message = \"%s\"\n", data->msg); // DEBUG
	ft_printf("message bits = %d = 0x%x\n", data->msg_len * 8, 8 * data->msg_len); // DEBUG
	if (message_padding(data) == FAILURE)
		return (FAILURE);
	fill_algo_constants(data);
	run_md5_algo(data);
	return (SUCCESS);
}
