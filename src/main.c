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


static void		clean_md5_data(t_md5 *data)
{
	free(data->padded_msg);
}

static void		clean_sha256_data(t_sha256 *data)
{
	free(data->padded_msg);
}

static void		clean_sha512_data(t_sha512 *data)
{
	free(data->padded_msg);
}

t_ex_ret	apply_md5(char *message)
{
	t_md5	data;

	if (!message)
		return (FAILURE);
	ft_bzero(&data, sizeof(data));
	data.msg = message;
	data.msg_len = ft_strlen(message);
	if (fill_md5_digest(&data) == FAILURE)
		return (FAILURE);
	hex_display(data.digest, MD5_DIGEST_BYTES);
	clean_md5_data(&data);
	return (SUCCESS);
}

t_ex_ret	apply_sha256(char *message)
{
	t_sha256	data;

	if (!message)
		return (FAILURE);
	ft_bzero(&data, sizeof(data));
	data.msg = message;
	data.msg_len = ft_strlen(message);
	if (fill_sha256_digest(&data) == FAILURE)
		return (FAILURE);
	hex_display(data.digest, SHA256_DIGEST_BYTES);
	clean_sha256_data(&data);
	return (SUCCESS);
}

t_ex_ret	apply_sha512(char *message)
{
	t_sha512	data;

	if (!message)
		return (FAILURE);
	ft_bzero(&data, sizeof(data));
	data.msg = message;
	data.msg_len = ft_strlen(message);
	if (fill_sha512_digest(&data) == FAILURE)
		return (FAILURE);
	hex_display(data.digest, SHA512_DIGEST_BYTES);
	clean_sha512_data(&data);
	return (SUCCESS);
}

int				main(int argc, char **argv) {

	if (argc != 3)
	{
		ft_dprintf(2, "./ft_ssl [algo] [str]\n");
		return (FAILURE);
	}
	if (!ft_strcmp(argv[1], "md5"))
	{
		if (apply_md5(argv[2]) == FAILURE)
			return (FAILURE);
	}
	else if (!ft_strcmp(argv[1], "sha256"))
	{
		if (apply_sha256(argv[2]) == FAILURE)
			return (FAILURE);
	}
	else if (!ft_strcmp(argv[1], "sha512"))
	{
		if (apply_sha512(argv[2]) == FAILURE)
			return (FAILURE);
	}
	return (SUCCESS);
}
