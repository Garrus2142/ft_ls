/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 12:55:13 by thugo             #+#    #+#             */
/*   Updated: 2017/02/20 12:53:19 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/types.h>
#include "ft_ls.h"

static char	*color(t_params *p, t_file *file)
{
	static char color[12];

	if (!(p->options & OPT_G))
		return (ft_strcpy(color, ""));
	if (S_ISDIR(file->stats.st_mode))
		return (ft_strcpy(color, "\033[1m"));
	else if (S_ISLNK(file->stats.st_mode))
		return (ft_strcpy(color, "\033[35m"));
	else if (S_ISSOCK(file->stats.st_mode))
		return (ft_strcpy(color, "\033[32m"));
	else if (S_ISFIFO(file->stats.st_mode))
		return (ft_strcpy(color, "\033[33m"));
	else if (file->stats.st_mode & S_ISUID && file->stats.st_mode &
			(S_IXUSR | S_IXGRP | S_IXOTH))
		return (ft_strcpy(color, "\033[30;41m"));
	else if (file->stats.st_mode & S_ISGID && file->stats.st_mode &
			(S_IXUSR | S_IXGRP | S_IXOTH))
		return (ft_strcpy(color, "\033[30;46m"));
	else if (file->stats.st_mode & (S_IXUSR | S_IXGRP | S_IXOTH))
		return (ft_strcpy(color, "\033[31m"));
	else if (S_ISBLK(file->stats.st_mode))
		return (ft_strcpy(color, "\033[34;46m"));
	else if (S_ISCHR(file->stats.st_mode))
		return (ft_strcpy(color, "\033[34;43m"));
	return (ft_strcpy(color, "\033[0m"));
}

static void	print_long2(t_params *p, t_file *par, t_file *file)
{
	if (S_ISBLK(file->stats.st_mode) || S_ISCHR(file->stats.st_mode))
	{
		ft_printf("  %3lu, %3lu", major(file->stats.st_rdev),
			minor(file->stats.st_rdev));
	}
	else
	{
		ft_printf("  %*lu", ft_max(par->size_max, ((par->infos & HAS_BLKCHR)
			* 8)), file->stats.st_size);
	}
	ft_printf(" %s %s%s%s", file->mtime, color(p, file),
		(file->infos & IS_OPERAND ? file->path : file->name),
		(p->options & OPT_G) ? "\033[0m" : "");
	if (S_ISLNK(file->stats.st_mode))
		ft_printf(" -> %s", file->linktarget);
	ft_putchar('\n');
}

static void	print_long(t_params *p, t_file *par, t_file *file)
{
	char	rights[12];
	char	*pw;
	char	*gr;

	if (!(pw = file->pw_name ? file->pw_name : ft_itoa(file->stats.st_uid)))
		exit(EXIT_FAILURE);
	if (!(gr = file->gr_name ? file->gr_name : ft_itoa(file->stats.st_gid)))
		exit(EXIT_FAILURE);
	get_rights(file, rights);
	ft_printf("%-11s %*lu %-*s  %-*s", rights, par->nlink_max, file->stats.
		st_nlink, par->n_pw_name, pw, par->n_gr_name, gr, par->size_max);
	free(pw);
	free(gr);
	print_long2(p, par, file);
}

void		display_file(t_params *p, t_file *file)
{
	t_list	*cur;

	if (file->name && (!(file->infos & IS_OPERAND) || p->nfiles > 1))
		ft_printf("%s%s:\n", (file->infos & IS_FIRST) ? "" : "\n", file->path);
	if (p->options & OPT_L_LOW)
	{
		file->nlink_max = ft_sizelong(file->nlink_max);
		file->size_max = ft_sizelong(file->size_max);
		if (file->infos & IS_OPERAND && !(S_ISDIR(file->stats.st_mode)))
			print_long(p, file, file);
		else if (file->name && file->childs)
			ft_printf("total %lu\n", file->total);
	}
	cur = file->childs;
	while (cur)
	{
		if (p->options & OPT_L_LOW)
			print_long(p, file, ACC_FILE(cur));
		else
		{
			ft_printf("%s%s%s\n", color(p, ACC_FILE(cur)), ACC_FILE(cur)->name,
				(p->options & OPT_G) ? "\033[0m" : "");
		}
		cur = cur->next;
	}
}
