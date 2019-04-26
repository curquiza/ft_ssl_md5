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

# define USAGE_INDENT "  "
# define HASH_ALGO_ERR "No available hash algorithm found"

# define OPTION_P		1 << 0
# define OPTION_Q		1 << 1
# define OPTION_R		1 << 2

typedef struct	s_hash_algo
{
	char		name[10];
	t_ex_ret	(*f)(t_hash *data, int alt);
	int			alt_param;
}				t_hash_algo;

typedef struct			s_state
{
	uint32_t	options;
	t_bool		output;
	t_bool		opt_end;
	t_hash_algo	*hash_algo;
}						t_state;

/*
** FUNCTIONS PROTOTYPES ********************************************************
*/
t_ex_ret    ret_usage_err();

void		first_init(t_hash_algo *algo_tab, t_state *state);
t_ex_ret	get_hash_algo(char *algo_arg, t_state *state, t_hash_algo *algo_tab);

t_ex_ret    apply_option(char *arg, t_state *state);
t_ex_ret    apply_file(char *arg, t_state *state);

// void		clean_hash_data(t_hash *data);

#endif
