#ifndef FT_SSL_H
# define FT_SSL_H

#include "libft.h"
#include "math.h"

# define MSG_LEN_BITS		64
# define MSG_LEN_BYTES		MSG_LEN_BITS / 8

# define MD5_CHUNK_BITS		512
# define MD5_CHUNK_BYTES	MD5_CHUNK_BITS / 8

# define MD5_DIGEST_BITS	128
# define MD5_DIGEST_BYTES	MD5_DIGEST_BITS / 8

# define MD5_WORD_NB		16

# define MD5_A0_INIT		0x67452301
# define MD5_B0_INIT		0xefcdab89
# define MD5_C0_INIT		0x98badcfe
# define MD5_D0_INIT		0x10325476

# define POW_2_32			0x100000000

typedef struct		s_md5_const
{
	uint32_t	shift;
	uint32_t	radian;
	uint32_t	(*func)(uint32_t b, uint32_t c, uint32_t d);
	int			word_index;
}					t_md5_const;

typedef struct		s_md5_incr
{
	uint32_t	a;
	uint32_t	b;
	uint32_t	c;
	uint32_t	d;
}					t_md5_incr;

typedef struct		s_md5
{
	t_byte		digest[MD5_DIGEST_BYTES];
	char		*msg;
	t_byte		*padded_msg;
	size_t		msg_len;
	size_t		padded_msg_len;
	t_md5_const	cst[MD5_CHUNK_BYTES];
	t_md5_incr	rslt;
}					t_md5;


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
** MD5
*/
t_ex_ret	fill_md5_digest(t_md5 *data);

#endif
