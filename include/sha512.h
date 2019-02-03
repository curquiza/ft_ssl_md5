#ifndef SHA512_H
# define SHA512_H

#include "libft.h"

# define SHA512_MSG_LEN_BITS		64
# define SHA512_MSG_LEN_BYTES		SHA512_MSG_LEN_BITS / 8

# define SHA512_CHUNK_BITS			512
# define SHA512_CHUNK_BYTES			SHA512_CHUNK_BITS / 8

# define SHA512_DIGEST_BITS			256
# define SHA512_DIGEST_BYTES		SHA512_DIGEST_BITS / 8

# define SHA512_WORD_NB_FROM_CHUNK	16
# define SHA512_WORD_NB				64

# define SHA512_A0_INIT				0x6a09e667
# define SHA512_B0_INIT				0xbb67ae85
# define SHA512_C0_INIT				0x3c6ef372
# define SHA512_D0_INIT				0xa54ff53a
# define SHA512_E0_INIT				0x510e527f
# define SHA512_F0_INIT				0x9b05688c
# define SHA512_G0_INIT				0x1f83d9ab
# define SHA512_H0_INIT				0x5be0cd19

typedef struct		s_sha512_incr
{
	uint32_t	a;
	uint32_t	b;
	uint32_t	c;
	uint32_t	d;
	uint32_t	e;
	uint32_t	f;
	uint32_t	g;
	uint32_t	h;
}					t_sha512_incr;

typedef struct		s_sha512
{
	t_byte		digest[SHA512_DIGEST_BYTES];
	char		*msg;
	t_byte		*padded_msg;
	size_t		msg_len;
	size_t		padded_msg_len;
	t_sha512_incr	rslt;
}					t_sha512;

uint32_t	g_k_sha512[SHA512_CHUNK_BYTES];

/*
** init
*/
t_ex_ret	message_padding_sha512(t_sha512 *data);

/*
** algo
*/
t_ex_ret	fill_sha512_digest(t_sha512 *data);

#endif
