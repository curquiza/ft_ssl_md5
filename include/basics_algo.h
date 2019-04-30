/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basics_algo.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <curquiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 18:10:57 by curquiza          #+#    #+#             */
/*   Updated: 2019/04/30 18:11:48 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BASICS_ALGO_H
# define BASICS_ALGO_H

# include "libft.h"

typedef struct		s_hash
{
	t_byte		*msg;
	t_byte		*padded_msg;
	t_byte		*digest;
	size_t		msg_len;
	size_t		padded_msg_len;
	size_t		digest_len;
}					t_hash;

/*
** Maths
*/
double				abs_double(double x);
double				floor_double(double x);

/*
** Conversion
*/
uint32_t			ptr_to_uint32(t_byte *str);
uint64_t			ptr_to_uint64(t_byte *str);
uint32_t			ptr_to_uint32_swap(t_byte *str);

/*
** Move
*/
uint32_t			left_rotate(uint32_t x, uint32_t n);
uint32_t			uint32_right_rotate(uint32_t x, uint32_t n);
uint32_t			uint32_right_shift(uint32_t x, uint32_t n);
uint64_t			uint64_right_rotate(uint64_t x, uint64_t n);
uint64_t			uint64_right_shift(uint64_t x, uint64_t n);

/*
** Misc
*/
void				*ft_memcpy_back(t_byte *dst, const void *src, size_t n);

#endif
