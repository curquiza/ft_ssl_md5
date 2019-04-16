#ifndef SHA1_H
# define SHA1_H

#include "libft.h"

# define SHA1_MSG_LEN_BITS	64
# define SHA1_MSG_LEN_BYTES	SHA1_MSG_LEN_BITS / 8

# define SHA1_CHUNK_BITS	512
# define SHA1_CHUNK_BYTES	SHA1_CHUNK_BITS / 8

# define SHA1_DIGEST_BITS	160
# define SHA1_DIGEST_BYTES	SHA1_DIGEST_BITS / 8

# define SHA1_WORD_NB_FROM_CHUNK	16
# define SHA1_WORD_NB				80

# define SHA1_ROUNDS				80

# define SHA1_A0_INIT		0x67452301
# define SHA1_B0_INIT		0xefcdab89
# define SHA1_C0_INIT		0x98badcfe
# define SHA1_D0_INIT		0x10325476
# define SHA1_E0_INIT		0xc3d2e1f0

typedef struct		s_sha1_const
{
	uint32_t	k;
	uint32_t	(*func)(uint32_t b, uint32_t c, uint32_t d);
}					t_sha1_const;

typedef struct		s_sha1_incr
{
	uint32_t	a;
	uint32_t	b;
	uint32_t	c;
	uint32_t	d;
	uint32_t	e;
}					t_sha1_incr;

/*
** init
*/
t_ex_ret	message_padding_sha1(t_hash *data);
void		fill_algo_constants_sha1(t_sha1_const *cst);

/*
** algo
*/
t_ex_ret	fill_sha1_digest(t_hash *data, int alt);

#endif
