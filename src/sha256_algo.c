#include "ft_ssl.h"

static void	padd_with_msg_size(t_sha256 *data, uint64_t *n)
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

static t_ex_ret	message_padding_sha256(t_sha256 *data)
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
	hex_display(data->padded_msg, data->padded_msg_len); //DEBUG
	return (SUCCESS);
}

t_ex_ret	fill_sha256_digest(t_sha256 *data)
{
	/* ft_printf("message = \"%s\"\n", data->msg); // DEBUG */
	/* ft_printf("message bits = %d = 0x%x\n", data->msg_len * 8, 8 * data->msg_len); // DEBUG */
	if (message_padding_sha256(data) == FAILURE)
		return (FAILURE);
	/* fill_algo_constants(data); */
	/* run_md5_algo(data); */
	return (SUCCESS);
}
