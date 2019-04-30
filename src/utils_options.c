/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_options.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <curquiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 18:33:26 by curquiza          #+#    #+#             */
/*   Updated: 2019/04/30 18:33:28 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

t_bool	opt_is_activated(uint32_t options_state, uint32_t opt_mask)
{
	return ((options_state & opt_mask) == opt_mask);
}

void	activate_opt(t_state *state, uint32_t opt_mask)
{
	state->options |= opt_mask;
}

void	desactivate_opt(t_state *state, uint32_t opt_mask)
{
	state->options ^= opt_mask;
}
