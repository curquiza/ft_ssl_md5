#include "ft_ssl.h"

static void		clean_md5_data(t_md5 *data)
{
	free(data->padded_msg);
}

static t_ex_ret	apply_md5(char *message)
{
	t_md5	data;

	if (!message)
		return (FAILURE);
	ft_bzero(&data, sizeof(data));
	data.msg = message;
	data.msg_len = ft_strlen(message);
	if (fill_md5_digest(&data) == FAILURE)
		return (FAILURE);
	clean_md5_data(&data);
	return (SUCCESS);
}

int				main(int argc, char **argv) {

	if (argc != 2)
	{
		ft_dprintf(2, "1 arg needed\n");
		exit(1);
	}
	if (apply_md5(argv[1]) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
