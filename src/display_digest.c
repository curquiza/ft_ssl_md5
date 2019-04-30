/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_digest.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <curquiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 18:34:12 by curquiza          #+#    #+#             */
/*   Updated: 2019/04/30 18:36:31 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	display_digest(char *arg, t_hash *data, t_state *state)
{
	char	*algo_name;

	if (opt_is_activated(state->options, OPTION_Q))
		hex_display_endl(data->digest, data->digest_len);
	else if (opt_is_activated(state->options, OPTION_R))
	{
		hex_display(data->digest, data->digest_len);
		if (opt_is_activated(state->options, OPTION_S))
			ft_printf(" \"%s\"\n", arg);
		else
			ft_printf(" %s\n", arg);
	}
	else
	{
		algo_name = state->hash_algo->name;
		ft_strupper(algo_name);
		if (opt_is_activated(state->options, OPTION_S))
			ft_printf("%s (\"%s\") = ", algo_name, arg);
		else
			ft_printf("%s (%s) = ", algo_name, arg);
		hex_display_endl(data->digest, data->digest_len);
	}
}
