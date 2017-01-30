/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 18:43:48 by thugo             #+#    #+#             */
/*   Updated: 2017/01/30 18:51:27 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	print_usage(char *cmd, char option)
{
	ft_printf("%s: illegal option -- %c\nusage: ls [-lRart] [file ...]\n",
		cmd, option);
}

void	read_args(int argc, char **argv, t_params *params)
{
	
}
