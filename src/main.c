#include "ft_ssl.h"

/* void		hex_display_details(t_byte *s, size_t len) */
/* { */
/* 	size_t		i; */
/*  */
/* 	i = 0; */
/* 	while (i < len) */
/* 	{ */
/* 		if (i % 4 == 0) */
/* 			ft_printf("%03d - %03d\t", i, i + 3); */
/* 		ft_printf("%02x", (t_byte)s[i]); */
/* 		i++; */
/* 		if (i % 4 == 0) */
/* 			write(1, "\n", 1); */
/* 		else */
/* 			write(1, " ", 1); */
/* 	} */
/* 	write(1, "\n", 1); */
/* } */
/*  */

// void		char_display(t_byte *s, size_t len)
// {
// 	size_t		i;

// 	i = 0;
// 	while (i < len)
// 	{
// 		ft_printf("%c", (t_byte)s[i]);
// 		i++;
// 	}
// 	write(1, "\n", 1);
// }

/************************** */

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

// t_ex_ret	get_options()
// {
// 	return SUCCESS;
// }

t_ex_ret		get_hash_algo(char *algo_arg, t_state *state, t_hash_algo *algo_tab)
{
	int		i;

	i = 0;
	while (i < HASH_FUNC_TAB_SIZE)
	{
		if (ft_strcmp(algo_tab[i].name, algo_arg) == 0)
		{
			state->hash_algo = &algo_tab[i];
			return SUCCESS;
		}
		i++;
	}
	return ft_ret_err(HASH_ALGO_ERR);
}

int				main(int argc, char **argv)
{
	t_hash_algo	algo_tab[HASH_FUNC_TAB_SIZE];
	t_state		state;

	if (argc <= 1)
		return ret_usage_err();
	first_init(algo_tab, &state);
	if (get_hash_algo(argv[1], &state, algo_tab) == FAILURE)
		return FAILURE;
	return SUCCESS;
}

// int				main(int argc, char **argv)
// {
// 	int		ret;
// 	t_hash	data;

// 	if (argc != 3)
// 	{
// 		ft_dprintf(2, "./ft_ssl [algo] [str]\n");
// 		return (FAILURE);
// 	}
// 	ret = SUCCESS;
// 	ft_bzero(&data, sizeof(data));
// 	if (get_options() == FAILURE || get_message(&data, argc, argv) == FAILURE)
// 		ret = FAILURE;
// 	else
// 		apply_hash_algo(&data, argv[1]);
// 	clean_hash_data(&data);
// 	return (ret);
// }