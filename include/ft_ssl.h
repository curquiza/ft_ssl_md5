#ifndef FT_SSL_H
# define FT_SSL_H

#include "libft.h"
#include "math.h" //needed ??

# define MSG_LEN_BITS		64
# define MSG_LEN_BYTES		MSG_LEN_BITS / 8

# define MD5_CHUNK_BITS		512
# define MD5_CHUNK_BYTES	MD5_CHUNK_BITS / 8

# define MD5_DIGEST_BITS	128
# define MD5_DIGEST_BYTES	MD5_DIGEST_BITS / 8

# define MD5_A0		0x67452301
# define MD5_B0		0xefcdab89
# define MD5_C0		0x98badcfe
# define MD5_D0		0x10325476

# define POW_2_32	0x100000000

typedef struct		s_md5_algo
{
	uint32_t		shift;
	uint32_t		sin_const;
	uint32_t		(*func)(uint32_t b, uint32_t c, uint32_t d);
}					t_md5_algo;

typedef struct		s_md5
{
	t_byte		digest[MD5_DIGEST_BYTES];
	char		*msg;
	t_byte		*padded_msg;
	size_t		msg_len;
	size_t		padded_msg_len;
	t_md5_algo	var[MD5_CHUNK_BYTES];
}					t_md5;

/* typedef struct		s_md5_input_const */
/* { */
/* 	int			shift[4]; */
/* 	uint32_t	(*func)(uint32_t b, uint32_t c, uint32_t d); */
/* }					t_md5_input_const; */

/*
** FUNCTIONS PROTOTYPES ********************************************************
*/

/* uint64_t	pow(uint32_t v, uint32_t n); */
double		pow_double(double v, uint32_t n);
double		abs_double(double x);

t_ex_ret	fill_md5_digest(t_md5 *data);

#endif
