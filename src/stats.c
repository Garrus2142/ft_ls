/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stats.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 09:05:09 by thugo             #+#    #+#             */
/*   Updated: 2017/02/19 18:16:10 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/types.h>
#include <grp.h>
#include <pwd.h>
#include "ft_ls.h"

void		file_get_stats(t_params *p, t_file *file)
{
	if (!(p->options & OPT_L_LOW) && file->infos & IS_OPERAND)
	{
		if (stat(file->path, &(file->stats)))
		{
			if (lstat(file->path, &(file->stats)) && !(file->infos & IS_ERROR))
				ls_error(file);
		}
	}
	else
	{
		if (lstat(file->path, &(file->stats)) && !(file->infos & IS_ERROR))
			ls_error(file);
	}
}

static void	set_uidgid(t_file *parent, t_file *file)
{
	struct passwd	*pwd;
	struct group	*grp;
	int				size;

	file->pw_name = NULL;
	if ((pwd = getpwuid(file->stats.st_uid)))
	{
		if (!(file->pw_name = ft_strdup(pwd->pw_name)))
			exit(EXIT_FAILURE);
		if ((size = ft_strlen(file->pw_name)) > parent->n_pw_name)
			parent->n_pw_name = size;
	}
	else if ((size = ft_sizelong(file->stats.st_uid)) > parent->n_pw_name)
		parent->n_pw_name = size;
	file->gr_name = NULL;
	if ((grp = getgrgid(file->stats.st_gid)))
	{
		if (!(file->gr_name = ft_strdup(grp->gr_name)))
			exit(EXIT_FAILURE);
		if ((size = ft_strlen(file->gr_name)) > parent->n_gr_name)
			parent->n_gr_name = size;
	}
	else if ((size = ft_sizelong(file->stats.st_gid)) > parent->n_gr_name)
		file->n_gr_name = size;
}

void		file_get_long_stats(t_file *parent, t_file *file)
{
	struct passwd	*pwd;
	struct group	*grp;

	parent->total += file->stats.st_blocks;
	if (file->stats.st_nlink > parent->nlink_max)
		parent->nlink_max = file->stats.st_nlink;
	set_uidgid(parent, file);
	if (S_ISBLK(file->stats.st_mode) || S_ISCHR(file->stats.st_mode))
		parent->infos = parent->infos | HAS_BLKCHR;
	else if (file->stats.st_size > parent->size_max)
		parent->size_max = file->stats.st_size;
}
