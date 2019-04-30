/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha1_cst_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <curquiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 18:31:52 by curquiza          #+#    #+#             */
/*   Updated: 2019/04/30 18:31:53 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

uint32_t	f_function_0_19(uint32_t b, uint32_t c, uint32_t d)
{
	return ((b & c) | (~b & d));
}

uint32_t	f_function_20_39(uint32_t b, uint32_t c, uint32_t d)
{
	return (b ^ c ^ d);
}

uint32_t	f_function_40_59(uint32_t b, uint32_t c, uint32_t d)
{
	return ((b & c) | (b & d) | (c & d));
}

uint32_t	f_function_60_79(uint32_t b, uint32_t c, uint32_t d)
{
	return (b ^ c ^ d);
}
