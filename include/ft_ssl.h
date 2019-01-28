#ifndef FT_SSL_H
# define FT_SSL_H

#include "libft.h"

# define MSG_LEN_BITS			64
# define MSG_LEN_BYTES			MSG_LEN_BITS / 8

# define MD5_DIGEST_CHUNK_BITS	512
# define MD5_DIGEST_CHUNK_BYTES	MD5_DIGEST_CHUNK_BITS / 8

# define MD5_DIGEST_BITS		128
# define MD5_DIGEST_BYTES		MD5_DIGEST_BITS / 8


typedef struct		s_md5
{
	char	*msg;
	t_byte	*padded_msg;
	size_t	msg_len;
	size_t	padded_msg_len;
	t_byte	digest[MD5_DIGEST_BYTES];
}					t_md5;

/*
** FUNCTIONS PROTOTYPES ********************************************************
*/

t_ex_ret	fill_md5_digest(t_md5 *data);

#endif
