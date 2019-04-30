/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <curquiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 18:55:10 by curquiza          #+#    #+#             */
/*   Updated: 2019/04/30 18:55:55 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

double	abs_double(double x)
{
	return (x < 0 ? -x : x);
}

double	floor_double(double x)
{
	return ((double)(uint32_t)x);
}
