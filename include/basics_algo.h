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
}	                t_hash;

/*
** Maths
*/
/* double		pow_double(double v, uint32_t n); */
double		abs_double(double x);
double		floor_double(double x);

/*
** Conversion
*/
uint32_t	ptr_to_uint32(t_byte *str);
uint64_t	ptr_to_uint64(t_byte *str);
uint32_t	ptr_to_uint32_swap(t_byte *str);

#endif