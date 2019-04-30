/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usage.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <curquiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 19:00:54 by curquiza          #+#    #+#             */
/*   Updated: 2019/04/30 19:01:45 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static void	print_usage(void)
{
	ft_printf("Usage: ./ft_ssl [algo] [options] [args]\n\n");
	ft_printf("Hash algorithms available:\n");
	ft_printf(USAGE_INDENT"md5\n");
	ft_printf(USAGE_INDENT"sha256\n");
	ft_printf(USAGE_INDENT"sha224\n");
	ft_printf(USAGE_INDENT"sha512\n");
	ft_printf(USAGE_INDENT"sha384\n");
	ft_printf(USAGE_INDENT"sha1\n\n");
	ft_printf("Options available:\n");
	ft_printf(USAGE_INDENT"-p: echo STDIN to STDOUT and append the checksum \
to STDOUT\n");
	ft_printf(USAGE_INDENT"-q: quiet mode\n");
	ft_printf(USAGE_INDENT"-r: reverse the format of the output\n");
	ft_printf(USAGE_INDENT"-s: print the sum of the given string\n");
}

t_ex_ret	ret_usage_err(void)
{
	print_usage();
	return (FAILURE);
}
