#ifndef SHA256_H
# define SHA256_H

#include "libft.h"

# define SHA256_MSG_LEN_BITS	64
# define SHA256_MSG_LEN_BYTES	SHA256_MSG_LEN_BITS / 8

# define SHA256_CHUNK_BITS		512
# define SHA256_CHUNK_BYTES	SHA256_CHUNK_BITS / 8

# define SHA256_DIGEST_BITS		256
# define SHA256_DIGEST_BYTES	SHA256_DIGEST_BITS / 8

# define SHA256_WORD_NB			64

# define SHA256_A0_INIT			0x6a09e667
# define SHA256_B0_INIT			0xbb67ae85
# define SHA256_C0_INIT			0x3c6ef372
# define SHA256_D0_INIT			0xa54ff53a
# define SHA256_E0_INIT			0x510e527f
# define SHA256_F0_INIT			0x9b05688c
# define SHA256_G0_INIT			0x1f83d9ab
# define SHA256_H0_INIT			0x5be0cd19

typedef struct		s_sha256_incr
{
	uint32_t	a;
	uint32_t	b;
	uint32_t	c;
	uint32_t	d;
	uint32_t	e;
	uint32_t	f;
	uint32_t	g;
	uint32_t	h;
}					t_sha256_incr;

typedef struct		s_sha256
{
	t_byte		digest[SHA256_DIGEST_BYTES];
	char		*msg;
	t_byte		*padded_msg;
	size_t		msg_len;
	size_t		padded_msg_len;
	t_sha256_incr	rslt;
}					t_sha256;

uint32_t	g_k_sha256[SHA256_CHUNK_BYTES];

/*
** init
*/
/* t_ex_ret	message_padding_sha256(t_sha256 *data); */

/*
** algo
*/
t_ex_ret	fill_sha256_digest(t_sha256 *data);

#endif
