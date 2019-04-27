#include "ft_ssl.h"

static t_ex_ret	close_fd(int fd)
{
	if (close(fd) == -1)
	{
		ft_dprintf(2, "Close error: %d: %s\n", fd, strerror(errno));
		return (FAILURE);
	}
	return (SUCCESS);
}

static t_ex_ret	read_message_from_file(int fd, t_hash *data)
{
	int		i;
	int		read_ret;
	t_byte	*tmp;
	char	buff[READ_BUFF_LEN];

	i = 0;
	while ((read_ret = read(fd, buff, READ_BUFF_LEN)) != 0)
	{
		if (read_ret == -1)
			return (FAILURE);
		tmp = data->msg;
		if (!(data->msg = (t_byte *)ft_memalloc(data->msg_len + read_ret)))
		{
			free(tmp);
			exit_malloc_err();
		}
		if (tmp)
			ft_memmove(data->msg, tmp, i);
		ft_memmove(data->msg + i, buff, read_ret);
		i += read_ret;
		free(tmp);
		data->msg_len += read_ret;
	}
	return (SUCCESS);
}

static t_ex_ret	get_message(char *filename, t_hash *data)
{
	int		fd;

	if ((fd = open(filename, O_RDONLY, 0)) == -1)
		return ft_ret_err2(filename, strerror(errno));
	if (read_message_from_file(fd, data) == FAILURE)
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
		return FAILURE;
	apply_hash_algo_for_arg(arg, &data, state);
	return SUCCESS;
}
