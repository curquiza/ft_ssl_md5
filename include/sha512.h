#ifndef SHA512_H
# define SHA512_H

#include "libft.h"

# define SHA512_MSG_LEN_BITS		128
# define SHA512_MSG_LEN_BYTES		SHA512_MSG_LEN_BITS / 8

# define SHA512_CHUNK_BITS			1024
# define SHA512_CHUNK_BYTES			SHA512_CHUNK_BITS / 8

# define SHA512_DIGEST_BITS			512
# define SHA512_DIGEST_BYTES		SHA512_DIGEST_BITS / 8

# define SHA512_ROUNDS				80

# define SHA512_WORD_NB_FROM_CHUNK	16
# define SHA512_WORD_NB				80

# define SHA512_A0_INIT				0x6a09e667f3bcc908
# define SHA512_B0_INIT				0xbb67ae8584caa73b
# define SHA512_C0_INIT				0x3c6ef372fe94f82b
# define SHA512_D0_INIT				0xa54ff53a5f1d36f1
# define SHA512_E0_INIT				0x510e527fade682d1
# define SHA512_F0_INIT				0x9b05688c2b3e6c1f
# define SHA512_G0_INIT				0x1f83d9abfb41bd6b
# define SHA512_H0_INIT				0x5be0cd19137e2179

# define SHA384_A0_INIT				0xcbbb9d5dc1059ed8
# define SHA384_B0_INIT				0x629a292a367cd507
# define SHA384_C0_INIT				0x9159015a3070dd17
# define SHA384_D0_INIT				0x152fecd8f70e5939
# define SHA384_E0_INIT				0x67332667ffc00b31
# define SHA384_F0_INIT				0x8eb44a8768581511
# define SHA384_G0_INIT				0xdb0c2e0d64f98fa7
# define SHA384_H0_INIT				0x47b5481dbefa4fa4

# define SHA384_DIGEST_BITS			384
# define SHA384_DIGEST_BYTES		SHA384_DIGEST_BITS / 8

typedef struct		s_sha512_incr
{
	uint64_t	a;
	uint64_t	b;
	uint64_t	c;
	uint64_t	d;
	uint64_t	e;
	uint64_t	f;
	uint64_t	g;
	uint64_t	h;
}					t_sha512_incr;

typedef unsigned	__int128 t_uint128;

uint64_t	g_k_sha512[SHA512_CHUNK_BYTES];

/*
** init
*/
void		message_padding_sha512(t_hash *data);

/*
** algo
*/
void		fill_sha512_digest(t_hash *data, int alt);

#endif
