#ifndef FT_SSL_H
# define FT_SSL_H

# include <math.h>
# include <errno.h>
# include <fcntl.h>

# include "libft.h"
# include "basics_algo.h"
# include "md5.h"
# include "sha256.h"
# include "sha512.h"
# include "sha1.h"

# define READ_BUFF_LEN	1000
# define HASH_FUNC_TAB_SIZE 6

typedef struct	s_hash_tab
{
	char		name[10];
	t_ex_ret	(*f)(t_hash *data, int alt);
	int			alt_param;
}				t_hash_tab;
// # define OPTION_P		1 << 0
// # define OPTION_Q		1 << 1
// # define OPTION_R		1 << 2

// typedef struct		s_input
// {
// 	uint32_t	options;
// 	char		*stdin_input;
// 	char		**opt_s_arg;
// 	char		**files_name;
// }					t_input;

/*
** FUNCTIONS PROTOTYPES ********************************************************
*/

void		clean_hash_data(t_hash *data);

/* void		hex_display(t_byte *s, size_t len); //DEBUG */
#endif
