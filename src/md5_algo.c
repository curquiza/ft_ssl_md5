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
	ft_memcpy(data->padded_msg, data->msg, data->msg_len);
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

uint32_t		get_sin_const(int i)
{
	return ((uint32_t)floor(abs_double(sin(i + 1)) * POW_2_32)); // /!\ FLOOR & SIN;
}

void		fill_0_15_constants(t_md5 *data)
{
	int			i;
	uint32_t		shift[4];

	shift[0] = 7;
	shift[1] = 12;
	shift[2] = 17;
	shift[3] = 22;
	i = 0;
	while (i < 16)
	{
		ft_printf("i = %d\n", i); //DEBUG
		data->var[i].shift = shift[i % 4];
		ft_printf("shift = %d\n", data->var[i].shift); //DEBUG
		data->var[i].sin_const = get_sin_const(i);
		ft_printf("sin_const = 0x%x\n", data->var[i].sin_const); //DEBUG
		data->var[i].func = &f_function;
		i++;
	}
}

void		fill_16_31_constants(t_md5 *data)
{
	int			i;
	uint32_t		shift[4];

	shift[0] = 5;
	shift[1] = 9;
	shift[2] = 14;
	shift[3] = 20;
	i = 16;
	while (i < 32)
	{
		ft_printf("i = %d\n", i); //DEBUG
		data->var[i].shift = shift[i % 4];
		ft_printf("shift = %d\n", data->var[i].shift); //DEBUG
		data->var[i].sin_const = get_sin_const(i);
		ft_printf("sin_const = 0x%x\n", data->var[i].sin_const); //DEBUG
		data->var[i].func = &g_function;
		i++;
	}
}

void		fill_32_47_constants(t_md5 *data)
{
	int			i;
	uint32_t		shift[4];

	shift[0] = 4;
	shift[1] = 11;
	shift[2] = 16;
	shift[3] = 23;
	i = 32;
	while (i < 48)
	{
		ft_printf("i = %d\n", i); //DEBUG
		data->var[i].shift = shift[i % 4];
		ft_printf("shift = %d\n", data->var[i].shift); //DEBUG
		data->var[i].sin_const = get_sin_const(i);
		ft_printf("sin_const = 0x%x\n", data->var[i].sin_const); //DEBUG
		data->var[i].func = &h_function;
		i++;
	}
}

void		fill_48_63_constants(t_md5 *data)
{
	int			i;
	uint32_t		shift[4];

	shift[0] = 6;
	shift[1] = 10;
	shift[2] = 15;
	shift[3] = 21;
	i = 48;
	while (i < 64)
	{
		ft_printf("i = %d\n", i); //DEBUG
		data->var[i].shift = shift[i % 4];
		ft_printf("shift = %d\n", data->var[i].shift); //DEBUG
		data->var[i].sin_const = get_sin_const(i);
		ft_printf("sin_const = 0x%x\n", data->var[i].sin_const); //DEBUG
		data->var[i].func = &i_function;
		i++;
	}
}

void		fill_algo_constants(t_md5 *data)
{
	fill_0_15_constants(data);
	fill_16_31_constants(data);
	fill_32_47_constants(data);
	fill_48_63_constants(data);
}

t_ex_ret	fill_md5_digest(t_md5 *data)
{
	ft_printf("message = \"%s\"\n", data->msg); // DEBUG
	ft_printf("message bits = %d = 0x%x\n", data->msg_len * 8, 8 * data->msg_len); // DEBUG
	if (message_padding(data) == FAILURE)
		return (FAILURE);
	fill_algo_constants(data);
	return (SUCCESS);
}
