#include "ft_ssl.h"

static t_ex_ret	read_message_from_fd(int fd, char *filename, t_hash *data)
{
	int		read_ret;
	char	buff[READ_BUFF_LEN];
	t_byte	*tmp;

	read_ret = 0;
	while ((read_ret = read(fd, buff, READ_BUFF_LEN)) > 0)
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
	if (read_ret == -1)
		return ft_ret_err2(filename, strerror(errno));
	return SUCCESS;
}

static t_ex_ret	close_fd(int fd)
{
	if (close(fd) == -1)
	{
		ft_dprintf(2, "Close error: %d: %s\n", fd, strerror(errno));
		return (FAILURE);
	}
	return (SUCCESS);
}

static t_ex_ret	get_message(char *filename, t_hash *data)
{
	int		fd;

	if ((fd = open(filename, O_RDONLY, 0)) == -1)
		return ft_ret_err2(filename, strerror(errno));
	if (read_message_from_fd(fd, filename, data) == FAILURE)
	{
		close_fd(fd);
		return (FAILURE);
	}
	return (close_fd(fd));
}

t_ex_ret	apply_file(char *arg, t_state *state)
{
	t_hash	data;

	ft_bzero(&data, sizeof(data));
	if (get_message(arg, &data) == FAILURE)
	{
		clean_hash_data(&data);
		return FAILURE;
	}
	apply_hash_algo_for_arg(arg, &data, state);
	return SUCCESS;
}
