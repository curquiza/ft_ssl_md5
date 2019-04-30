#include "ft_ssl.h"

// static char	*get_stdin_input(void)
// {
// 	char	line[READ_BUFF_LEN + 1];
// 	char	*rslt;
// 	char	*tmp;
// 	int		ret;

// 	if (!(rslt = ft_strdup("")))
// 		exit_malloc_err();
// 	ft_bzero(line, READ_BUFF_LEN + 1);
// 	while ((ret = read(0, line, READ_BUFF_LEN)) > 0)
// 	{
// 		tmp = rslt;
// 		line[ret] = '\0';
// 		if (!(rslt = ft_strjoin(tmp, line)))
// 		{
// 			ft_strdel(&tmp);
// 			exit_malloc_err();
// 		}
// 		ft_strdel(&tmp);
// 	}
// 	close(0);
// 	return (rslt);
// }

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

void	apply_stdin(t_state *state)
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
