#include "ft_ssl.h"

static t_ex_ret	apply_md5(char *message)
{
	t_byte	md5_digest[MD5_DIGEST_BYTES];

	ft_bzero(md5_digest, MD5_DIGEST_BYTES);
	if (fill_md5_digest(message, md5_digest) == FAILURE)
		return (FAILURE);
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
