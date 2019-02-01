#ifndef SHA256_H
# define SHA256_H

#include "libft.h"

# define SHA256_MSG_LEN_BITS	64
# define SHA256_MSG_LEN_BYTES	SHA256_MSG_LEN_BITS / 8

# define SHA256_CHUNK_BITS		512
# define SHA256_CHUNK_BYTES	SHA256_CHUNK_BITS / 8

# define SHA256_DIGEST_BITS		256
# define SHA256_DIGEST_BYTES	SHA256_DIGEST_BITS / 8

typedef struct		s_sha256
{
	t_byte		digest[SHA256_DIGEST_BYTES];
	char		*msg;
	t_byte		*padded_msg;
	size_t		msg_len;
	size_t		padded_msg_len;
	/* t_md5_const	cst[MD5_CHUNK_BYTES]; */
	/* t_md5_incr	rslt; */
}					t_sha256;

/*
** init
*/
/* t_ex_ret	message_padding_sha256(t_sha256 *data); */

/*
** algo
*/
t_ex_ret	fill_sha256_digest(t_sha256 *data);

#endif
