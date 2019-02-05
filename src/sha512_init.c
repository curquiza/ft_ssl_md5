#include "ft_ssl.h"

// DEBUG
/* void		uint8_display(t_byte *s, size_t len) */
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

static void	padd_with_msg_size(t_hash *data, t_uint128 *n)
{
	int		i;
	int		addr;

	i = SHA512_MSG_LEN_BYTES - 1;
	addr = data->padded_msg_len - SHA512_MSG_LEN_BYTES;
	while (i >= 0)
	{
		data->padded_msg[addr] = ((t_byte *)n)[i];
		i--;
		addr++;
	}
}

t_ex_ret	message_padding_sha512(t_hash *data)
{
	size_t		tmp_len;
	t_uint128	msg_len_bits;

	tmp_len = (data->msg_len + 1 + SHA512_MSG_LEN_BYTES);
	if (tmp_len % (SHA512_CHUNK_BYTES) == 0)
		data->padded_msg_len = tmp_len;
	else
		data->padded_msg_len = (tmp_len / (SHA512_CHUNK_BYTES) + 1)
					* (SHA512_CHUNK_BYTES);
	if (!(data->padded_msg = (t_byte *)ft_memalloc(data->padded_msg_len)))
		return (FAILURE);
	/* ft_printf("padded_msg len = %d = 0x%x\n", data->padded_msg_len, data->padded_msg_len); //DEBUG */
	ft_memmove(data->padded_msg, data->msg, data->msg_len);
	data->padded_msg[data->msg_len] = (t_byte)(1 << 7);
	msg_len_bits = 8 * data->msg_len;
	padd_with_msg_size(data, &msg_len_bits);
	/* uint8_display(data->padded_msg, data->padded_msg_len); //DEBUG */
	return (SUCCESS);
}
