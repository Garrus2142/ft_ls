/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 18:43:48 by thugo             #+#    #+#             */
/*   Updated: 2017/02/18 16:42:57 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_ls.h"

static void	print_usage(char *cmd, char option)
{
	ft_printf("%s: illegal option -- %c\nusage: ft_ls [-%s] [file ...]\n",
		cmd, option, "lRartG1");
	exit(EXIT_FAILURE);
}

static void	check_option(char *cmd, char *options, t_params *params)
{
	int	i;

	i = -1;
	while (options[++i])
	{
		if (options[i] == 'l')
			params->options = params->options | OPT_L_LOW;
		else if (options[i] == 'R')
			params->options = params->options | OPT_R;
		else if (options[i] == 'a')
			params->options = params->options | OPT_A_LOW;
		else if (options[i] == 'r')
			params->options = params->options | OPT_R_LOW;
		else if (options[i] == 't')
			params->options = params->options | OPT_T_LOW;
		else if (options[i] == 'G')
			params->options = params->options | OPT_G;
		else if (options[i] == '1')
			params->options = params->options | OPT_1;
		else
			print_usage(cmd, options[i]);
	}
}

static void	copy_files(char **files, int n, t_params *params)
{
	int	i;

	params->nfiles = n;
	if (!(params->files = (char **)malloc(sizeof(char *) * n)))
		exit(EXIT_FAILURE);
	i = -1;
	while (++i < n)
	{
		if (!(params->files[i] = ft_strdup(files[i])))
			exit(EXIT_FAILURE);
	}
}

void		read_args(int argc, char **argv, t_params *params)
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
			check_option(argv[0], argv[i] + 1, params);
		else
		{
			copy_files(argv + i, argc - i, params);
			return ;
		}
	}
	params->nfiles = 1;
	if (!(params->files = (char **)malloc(sizeof(char *))))
		exit(EXIT_FAILURE);
	if (!(params->files[0] = ft_strdup(".")))
		exit(EXIT_FAILURE);
}
