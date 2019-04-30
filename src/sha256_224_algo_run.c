/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_224_algo_run.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <curquiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 18:32:11 by curquiza          #+#    #+#             */
/*   Updated: 2019/04/30 18:47:15 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static void	rslt_init(t_sha256_incr *rslt, int alt)
{
	if (alt == 0)
	{
		rslt->a = SHA256_A0_INIT;
		rslt->b = SHA256_B0_INIT;
		rslt->c = SHA256_C0_INIT;
		rslt->d = SHA256_D0_INIT;
		rslt->e = SHA256_E0_INIT;
		rslt->f = SHA256_F0_INIT;
		rslt->g = SHA256_G0_INIT;
		rslt->h = SHA256_H0_INIT;
	}
	else
	{
		rslt->a = SHA224_A0_INIT;
		rslt->b = SHA224_B0_INIT;
		rslt->c = SHA224_C0_INIT;
		rslt->d = SHA224_D0_INIT;
		rslt->e = SHA224_E0_INIT;
		rslt->f = SHA224_F0_INIT;
		rslt->g = SHA224_G0_INIT;
		rslt->h = SHA224_H0_INIT;
	}
}

static void	fill_digest(t_hash *data, t_sha256_incr *rslt, int alt)
{
	size_t	sizeof_uint32;

	if (!(data->digest = ft_memalloc(data->digest_len)))
		exit_malloc_err_with_clean(data);
	sizeof_uint32 = sizeof(uint32_t);
	ft_memcpy_back(data->digest, &rslt->a, sizeof_uint32);
	ft_memcpy_back(data->digest + sizeof_uint32, &rslt->b, sizeof_uint32);
	ft_memcpy_back(data->digest + 2 * sizeof_uint32, &rslt->c, sizeof_uint32);
	ft_memcpy_back(data->digest + 3 * sizeof_uint32, &rslt->d, sizeof_uint32);
	ft_memcpy_back(data->digest + 4 * sizeof_uint32, &rslt->e, sizeof_uint32);
	ft_memcpy_back(data->digest + 5 * sizeof_uint32, &rslt->f, sizeof_uint32);
	ft_memcpy_back(data->digest + 6 * sizeof_uint32, &rslt->g, sizeof_uint32);
	if (alt == 0)
		ft_memcpy_back(data->digest + 7 * sizeof_uint32, &rslt->h,
			sizeof_uint32);
}

void		run_sha256_224_algo(t_hash *data, int alt)
{
	uint32_t		i;
	uint32_t		words[SHA256_WORD_NB];
	t_sha256_incr	rslt;

	rslt_init(&rslt, alt);
	i = 0;
	while (i < (data->padded_msg_len / (SHA256_CHUNK_BYTES)))
	{
		fill_words_sha256_224(words, i, data);
		run_one_chunk_sha256_224(words, &rslt);
		i++;
	}
	fill_digest(data, &rslt, alt);
}
