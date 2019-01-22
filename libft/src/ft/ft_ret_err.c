/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ret_err.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <curquiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 09:33:03 by curquiza          #+#    #+#             */
/*   Updated: 2018/11/21 12:55:10 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_ex_ret	ft_ret_err(char *s)
{
	ft_dprintf(2, "Error: %s\n", s);
	return (FAILURE);
}
