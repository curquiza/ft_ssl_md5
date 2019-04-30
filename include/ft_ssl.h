/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <curquiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 18:12:09 by curquiza          #+#    #+#             */
/*   Updated: 2019/04/30 18:14:27 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include <math.h>
# include <errno.h>
# include <fcntl.h>

# include "libft.h"
# include "basics_algo.h"
# include "md5.h"
# include "sha256_224.h"
# include "sha512_384.h"
# include "sha1.h"

# define READ_BUFF_LEN		100000
# define HASH_FUNC_TAB_SIZE	6

# define USAGE_INDENT		"  "
# define READ_ERR			"Reading file error"
# define HASH_ALGO_ERR		"No available hash algorithm found"
# define OPT_S_ERR			"Option -s requires an argument"

# define OPTION_P_CHAR		'p'
# define OPTION_Q_CHAR		'q'
# define OPTION_R_CHAR		'r'
# define OPTION_S_CHAR		's'
# define OPTION_P			1 << 0
# define OPTION_Q			1 << 1
# define OPTION_R			1 << 2
# define OPTION_S			1 << 3

typedef struct			s_hash_algo
{
	char		name[10];
	void		(*f)(t_hash *data);
}						t_hash_algo;

typedef struct			s_state
{
	uint32_t	options;
	t_bool		output;
	t_bool		opt_end;
	t_bool		opt_s;
	t_hash_algo	*hash_algo;
}						t_state;

/*
** FUNCTIONS PROTOTYPES ********************************************************
*/

/*
** Utils
*/
t_ex_ret				ret_usage_err();
void					hex_display(t_byte *s, size_t len);
void					hex_display_endl(t_byte *s, size_t len);
t_bool					opt_is_activated(uint32_t options_state,
							uint32_t opt_mask);
void					activate_opt(t_state *state, uint32_t opt_mask);
void					desactivate_opt(t_state *state, uint32_t opt_mask);
void					exit_malloc_err(void);
void					exit_malloc_err_with_clean(t_hash *data);

/*
** Main functions
*/
void					first_init(t_hash_algo *algo_tab, t_state *state);
t_ex_ret				get_hash_algo(char *algo_arg, t_state *state,
							t_hash_algo *algo_tab);

t_ex_ret				apply_file(char *arg, t_state *state);
void					apply_stdin(t_state *state);
void					apply_option(char *arg, char *next_arg, t_state *state);
void					apply_hash_algo_for_arg(char *arg, t_hash *data,
							t_state *state);
t_ex_ret				run_ft_ssl(char **argv, t_state *state);

void					display_digest(char *filename, t_hash *data,
							t_state *state);

void					clean_hash_data(t_hash *data);

#endif
