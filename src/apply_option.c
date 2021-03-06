/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_option.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <curquiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 18:33:44 by curquiza          #+#    #+#             */
/*   Updated: 2019/04/30 18:38:07 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static void	apply_option_s(char *arg, char *next_arg, t_state *state)
{
	t_hash	data;
	char	*s_arg;

	state->output = TRUE;
	state->opt_s = TRUE;
	if (!*(arg + 1))
	{
		s_arg = next_arg;
		if (!next_arg)
		{
			ft_dprintf(2, "Error: %s\n", OPT_S_ERR);
			exit(FAILURE);
		}
	}
	else
		s_arg = arg + 1;
	ft_bzero(&data, sizeof(data));
	if (!(data.msg = (t_byte *)strdup(s_arg)))
		exit_malloc_err();
	data.msg_len = ft_strlen(s_arg);
	apply_hash_algo_for_arg(s_arg, &data, state);
}

static void	switch_between_option(char *arg, char *next_arg, t_state *state)
{
	if (*arg == OPTION_P_CHAR)
	{
		activate_opt(state, OPTION_P);
		apply_stdin(state);
	}
	else if (*arg == OPTION_Q_CHAR)
		activate_opt(state, OPTION_Q);
	else if (*arg == OPTION_R_CHAR)
		activate_opt(state, OPTION_R);
	else if (*arg == OPTION_S_CHAR)
	{
		activate_opt(state, OPTION_S);
		apply_option_s(arg, next_arg, state);
		desactivate_opt(state, OPTION_S);
	}
	else
	{
		ft_dprintf(2, "Error: %c: illegal option\n", *arg);
		exit(FAILURE);
	}
}

void		apply_option(char *arg, char *next_arg, t_state *state)
{
	arg++;
	while (*arg)
	{
		if (state->opt_s)
		{
			state->opt_s = FALSE;
			break ;
		}
		switch_between_option(arg, next_arg, state);
		arg++;
	}
}
