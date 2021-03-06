/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512_384_padding.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <curquiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 18:32:47 by curquiza          #+#    #+#             */
/*   Updated: 2019/04/30 18:49:22 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

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

void		message_padding_sha512_384(t_hash *data)
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
		exit_malloc_err_with_clean(data);
	ft_memmove(data->padded_msg, data->msg, data->msg_len);
	data->padded_msg[data->msg_len] = (t_byte)(1 << 7);
	msg_len_bits = 8 * data->msg_len;
	padd_with_msg_size(data, &msg_len_bits);
}
