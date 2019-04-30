/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512_384_algo_main.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <curquiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 18:32:33 by curquiza          #+#    #+#             */
/*   Updated: 2019/04/30 18:49:07 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static void	fill_sha512_384_digest(t_hash *data, int alt)
{
	if (alt == 0)
		data->digest_len = SHA512_DIGEST_BYTES;
	else
		data->digest_len = SHA384_DIGEST_BYTES;
	message_padding_sha512_384(data);
	run_sha512_384_algo(data, alt);
}

void		fill_sha512_digest(t_hash *data)
{
	fill_sha512_384_digest(data, 0);
}

void		fill_sha384_digest(t_hash *data)
{
	fill_sha512_384_digest(data, 1);
}
