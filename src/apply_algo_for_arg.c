/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_algo_for_arg.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <curquiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 18:33:40 by curquiza          #+#    #+#             */
/*   Updated: 2019/04/30 18:33:41 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	apply_hash_algo_for_arg(char *arg, t_hash *data, t_state *state)
{
	state->hash_algo->f(data);
	display_digest(arg, data, state);
	clean_hash_data(data);
}
