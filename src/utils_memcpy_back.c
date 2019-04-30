/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_memcpy_back.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <curquiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 18:33:22 by curquiza          #+#    #+#             */
/*   Updated: 2019/04/30 18:33:23 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	*ft_memcpy_back(t_byte *dst, const void *src, size_t n)
{
	int				i;
	size_t			j;

	i = n - 1;
	j = 0;
	while (i >= 0)
	{
		dst[j] = ((t_byte *)src)[i];
		i--;
		j++;
	}
	return (dst);
}
