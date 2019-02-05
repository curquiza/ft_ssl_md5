#ifndef BASICS_H
# define BASICS_H

#include "libft.h"

typedef struct		s_hash
{
	char		*msg;
	t_byte		*padded_msg;
	t_byte		*digest;
	size_t		msg_len;
	size_t		padded_msg_len;
	size_t		digest_len;
}					t_hash;

#endif
