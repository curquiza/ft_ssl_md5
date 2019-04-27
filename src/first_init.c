#include "ft_ssl.h"

static void		init_one_func(t_hash_algo *tab, char *name, t_ex_ret (*f)(t_hash *data, int alt), int alt_param)
{
	ft_strcpy(tab->name, name);
	tab->f = f;
	tab->alt_param = alt_param;
}

static void		init_hash_func_tab(t_hash_algo *tab)
{
	init_one_func(&tab[0], "md5", &fill_md5_digest, 0);
	init_one_func(&tab[1], "sha256", &fill_sha256_digest, 0);
	init_one_func(&tab[2], "sha224", &fill_sha256_digest, 1);
	init_one_func(&tab[3], "sha512", &fill_sha512_digest, 0);
	init_one_func(&tab[4], "sha384", &fill_sha512_digest, 1);
	init_one_func(&tab[5], "sha1", &fill_sha1_digest, 0);
}

void		first_init(t_hash_algo *algo_tab, t_state *state)
{
	init_hash_func_tab(algo_tab);
	ft_bzero(state, sizeof(state));
}
