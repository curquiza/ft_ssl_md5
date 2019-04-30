/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <curquiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 18:56:39 by curquiza          #+#    #+#             */
/*   Updated: 2019/04/30 18:56:58 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static void		init_one_func(t_hash_algo *tab, char *name,
					void (*f)(t_hash *data))
{
	ft_strcpy(tab->name, name);
	tab->f = f;
}

static void		init_hash_func_tab(t_hash_algo *tab)
{
	init_one_func(&tab[0], "md5", &fill_md5_digest);
	init_one_func(&tab[1], "sha256", &fill_sha256_digest);
	init_one_func(&tab[2], "sha224", &fill_sha224_digest);
	init_one_func(&tab[3], "sha512", &fill_sha512_digest);
	init_one_func(&tab[4], "sha384", &fill_sha384_digest);
	init_one_func(&tab[5], "sha1", &fill_sha1_digest);
}

void			first_init(t_hash_algo *algo_tab, t_state *state)
{
	init_hash_func_tab(algo_tab);
	ft_bzero(state, sizeof(state));
}
