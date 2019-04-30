/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_stdin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <curquiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 18:33:49 by curquiza          #+#    #+#             */
/*   Updated: 2019/04/30 18:37:52 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static void	read_message_from_stdin(t_hash *data)
{
	int		read_ret;
	char	buff[READ_BUFF_LEN];
	t_byte	*tmp;

	read_ret = 0;
	while ((read_ret = read(0, buff, READ_BUFF_LEN)) > 0)
	{
		tmp = data->msg;
		if (!(data->msg = (t_byte *)malloc(data->msg_len + read_ret)))
		{
			free(tmp);
			exit_malloc_err_with_clean(data);
		}
		if (tmp)
			ft_memmove(data->msg, tmp, data->msg_len);
		ft_memmove(data->msg + data->msg_len, buff, read_ret);
		data->msg_len += read_ret;
		free(tmp);
	}
	close(0);
}

void		apply_stdin(t_state *state)
{
	t_hash	data;

	ft_bzero(&data, sizeof(data));
	read_message_from_stdin(&data);
	state->hash_algo->f(&data);
	if (opt_is_activated(state->options, OPTION_P))
		write(1, data.msg, data.msg_len);
	hex_display_endl(data.digest, data.digest_len);
	clean_hash_data(&data);
}
