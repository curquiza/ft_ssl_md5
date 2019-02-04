#ifndef FT_SSL_H
# define FT_SSL_H

# include "math.h"

# include "libft.h"
# include "md5.h"
# include "sha256.h"
# include "sha512.h"

/*
** FUNCTIONS PROTOTYPES ********************************************************
*/

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

/* void		hex_display(t_byte *s, size_t len); //DEBUG */
#endif
