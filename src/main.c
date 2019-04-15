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

void		hex_display(t_byte *s, size_t len)
{
	size_t		i;

	i = 0;
	while (i < len)
	{
		ft_printf("%02x", (t_byte)s[i]);
		i++;
	}
	write(1, "\n", 1);
}

void		char_display(t_byte *s, size_t len)
{
	size_t		i;

	i = 0;
	while (i < len)
	{
		ft_printf("%c", (t_byte)s[i]);
		i++;
	}
	write(1, "\n", 1);
}

t_ex_ret	fill_digest(char *algo, t_hash *data)
{
	if (!ft_strcmp(algo, "md5"))
	{
		if (fill_md5_digest(data, 0) == FAILURE)
			return (FAILURE);
	}
	else if (!ft_strcmp(algo, "sha256"))
	{
		if (fill_sha256_digest(data, 0) == FAILURE)
			return (FAILURE);
	}
	else if (!ft_strcmp(algo, "sha224"))
	{
		if (fill_sha256_digest(data, 1) == FAILURE)
			return (FAILURE);
	}
	else if (!ft_strcmp(algo, "sha512"))
	{
		if (fill_sha512_digest(data, 0) == FAILURE)
			return (FAILURE);
	}
	else if (!ft_strcmp(algo, "sha384"))
	{
		if (fill_sha512_digest(data, 1) == FAILURE)
			return (FAILURE);
	}
	else if (!ft_strcmp(algo, "sha1"))
	{
		if (fill_sha1_digest(data, 0) == FAILURE)
			return (FAILURE);
	}
	return (SUCCESS);
}

void		init_one_func(t_hash_tab *tab, char *name, t_ex_ret	(*f)(t_hash *data, int alt), int alt_param)
{
	ft_strcpy(tab->name, name);
	tab->f = f;
	tab->alt_param = alt_param;
}

void		init_hash_func_tab(t_hash_tab *tab)
{
	init_one_func(&tab[0], "md5", &fill_md5_digest, 0);
	init_one_func(&tab[1], "sha256", &fill_sha256_digest, 0);
	init_one_func(&tab[2], "sha224", &fill_sha256_digest, 1);
	init_one_func(&tab[3], "sha512", &fill_sha512_digest, 0);
	init_one_func(&tab[4], "sha384", &fill_sha512_digest, 1);
	init_one_func(&tab[5], "sha1", &fill_sha1_digest, 0);
}

t_ex_ret	apply_hash_algo(t_hash *data, char *algo)
{
	t_hash_tab		tab[HASH_FUNC_TAB_SIZE];
	int 			i;

	init_hash_func_tab(tab);
	i = 0;
	while (i < HASH_FUNC_TAB_SIZE)
	{
		if (ft_strcmp(tab[i].name, algo) == 0)
		{
			if (tab[i].f(data, tab[i].alt_param) == FAILURE)
				return FAILURE;
			else
				break ;
		}
		i++;
	}
	hex_display(data->digest, data->digest_len);
	return (SUCCESS);
}

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

t_ex_ret	get_options()
{
	return SUCCESS;
}

int				main(int argc, char **argv) {

	int		ret;
	t_hash	data;

	if (argc != 3)
	{
		ft_dprintf(2, "./ft_ssl [algo] [str]\n");
		return (FAILURE);
	}
	ret = SUCCESS;
	ft_bzero(&data, sizeof(data));
	if (get_options() == FAILURE || get_message(&data, argc, argv) == FAILURE)
		ret = FAILURE;
	else
		apply_hash_algo(&data, argv[1]);
	clean_hash_data(&data);
	return (ret);
}
