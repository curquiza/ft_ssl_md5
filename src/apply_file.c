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
