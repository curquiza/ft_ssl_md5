/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_malloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <curquiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 18:33:19 by curquiza          #+#    #+#             */
/*   Updated: 2019/04/30 18:33:20 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void		exit_malloc_err(void)
{
	ft_dprintf(2, "Malloc error\n");
	exit(FAILURE);
}

void		exit_malloc_err_with_clean(t_hash *data)
{
	clean_hash_data(data);
	ft_dprintf(2, "Malloc error\n");
	exit(FAILURE);
}
