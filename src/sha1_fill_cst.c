/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha1_fill_cst.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <curquiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 18:31:56 by curquiza          #+#    #+#             */
/*   Updated: 2019/04/30 18:42:21 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static void		fill_constants(t_sha1_const *cst, int start, uint32_t k,
						uint32_t (*func)(uint32_t b, uint32_t c, uint32_t d))
{
	int		i;

	i = start;
	while (i < start + 20)
	{
		cst[i].k = k;
		cst[i].func = func;
		i++;
	}
}

void			fill_algo_constants_sha1(t_sha1_const *cst)
{
	fill_constants(cst, 0, 0x5a827999, &f_function_0_19);
	fill_constants(cst, 20, 0x6ed9eba1, &f_function_20_39);
	fill_constants(cst, 40, 0x8f1bbcdc, &f_function_40_59);
	fill_constants(cst, 60, 0xca62c1d6, &f_function_60_79);
}
