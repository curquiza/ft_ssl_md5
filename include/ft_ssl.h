#ifndef FT_SSL_H
# define FT_SSL_H

#include "libft.h"

# define MSG_LEN_BITS			64
# define MSG_LEN_BYTES			MSG_LEN_BITS / 8

# define MD5_DIGEST_CHUNK_BITS	512
# define MD5_DIGEST_CHUNK_BYTES	MD5_DIGEST_CHUNK_BITS / 8

# define MD5_DIGEST_BITS		128
# define MD5_DIGEST_BYTES		MD5_DIGEST_BITS / 8
/*
** FUNCTIONS PROTOTYPES ********************************************************
*/

t_ex_ret	fill_md5_digest(char *message, t_byte *digest);

#endif
