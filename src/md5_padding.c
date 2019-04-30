#include "ft_ssl.h"

static void	padd_with_msg_size(t_hash *data, uint64_t *n)
{
	int		i;
	int		addr;

	i = 0;
	addr = data->padded_msg_len - MD5_MSG_LEN_BYTES;
	while (i < (MD5_MSG_LEN_BYTES))
	{
		data->padded_msg[addr] = ((t_byte *)n)[i];
		i++;
		addr++;
	}
}

void	message_padding_md5(t_hash *data)
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
		exit_malloc_err_with_clean(data);
	ft_memmove(data->padded_msg, data->msg, data->msg_len);
	data->padded_msg[data->msg_len] = (t_byte)(1 << 7);
	msg_len_bits = 8 * data->msg_len;
	padd_with_msg_size(data, &msg_len_bits);
}
