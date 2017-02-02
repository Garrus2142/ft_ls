/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 18:43:48 by thugo             #+#    #+#             */
/*   Updated: 2017/02/02 15:45:25 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_ls.h"
#include "../libft/libft.h"

static void	print_usage(char option)
{
	ft_printf("ft_ls: illegal option -- %c\nusage: ft_ls [-lRart] [file ...]\n",
		option);
	exit(EXIT_SUCCESS);
}

static void	check_option(char *options, t_params *params)
{
	int	i;

	i = -1;
	while (options[++i])
	{
		if (options[i] == 'l')
			params->options = params->options | OPT_l;
		else if (options[i] == 'R')
			params->options = params->options | OPT_R;
		else if (options[i] == 'a')
			params->options = params->options | OPT_a;
		else if (options[i] == 'r')
			params->options = params->options | OPT_r;
		else if (options[i] == 't')
			params->options = params->options | OPT_t;
		else
			print_usage(options[i]);
	}
}

void	read_args(int argc, char **argv, t_params *params)
{
	int		i;
	char	endopt;

	params->options = 0;
	params->nfiles = 0;
	endopt = 0;
	i = 0;
	while (++i < argc)
	{
		if (!endopt && ft_strcmp(argv[i], "--") == 0)
			endopt = 1;
		else if (!endopt && ft_strlen(argv[i]) > 1 && argv[i][0] == '-')
			check_option(argv[i] + 1, params);
		else
		{
			params->files = argv + i;
			params->nfiles = argc - i;
			break ;
		}
	}
}
