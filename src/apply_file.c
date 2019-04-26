#include "ft_ssl.h"

t_ex_ret	close_fd(int fd)
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
			return (FAILURE);
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

t_ex_ret	get_message(t_hash *data, int argc, char **argv)
{
	int		fd;

	(void)argc; //DEBUG
	if ((fd = open(argv[2], O_RDONLY, 0)) == -1)
	{
		data->msg_len = ft_strlen(argv[2]);
		data->msg = (t_byte *)ft_memalloc(data->msg_len);
		ft_memmove(data->msg, argv[2], data->msg_len);
		return (SUCCESS);
	}
	if (read_message_from_file(fd, data) == FAILURE)
	{
		close_fd(fd);
		return (FAILURE);
	}
	return (close_fd(fd));
}

t_ex_ret    apply_file(char *arg, t_state *state)
{
    (void)arg;
    (void)state;
    return SUCCESS;
}