/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stats.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 09:05:09 by thugo             #+#    #+#             */
/*   Updated: 2017/02/20 11:01:53 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/types.h>
#include <sys/param.h>
#include <time.h>
#include <grp.h>
#include <pwd.h>
#include <unistd.h>
#include "ft_ls.h"

int			file_get_stats(t_params *p, t_file *file)
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
	return (!(file->infos & IS_ERROR));
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

static void	set_mdate(t_file *file)
{
	static time_t	timenow;
	char			*strtime;

	ft_memset(file->mtime, ' ', 12);
	file->mtime[12] = '\0';
	if (timenow == 0)
		timenow = time(NULL);
	if (!(strtime = ctime(&(file->stats.st_mtimespec.tv_sec))))
		return ;
	ft_memcpy(file->mtime, strtime + 4, 6);
	if (file->stats.st_mtimespec.tv_sec >= 253402297200)
		ft_strcpy(file->mtime + 8, "10000");
	else if (file->stats.st_mtimespec.tv_sec > timenow ||
			file->stats.st_mtimespec.tv_sec < timenow - ((365 / 2) * 86400))
		ft_memcpy(file->mtime + 8, strtime + 20, 4);
	else
		ft_memcpy(file->mtime + 7, strtime + 11, 5);
}

void		file_get_long_stats(t_file *parent, t_file *file)
{
	struct passwd	*pwd;
	struct group	*grp;

	parent->total += file->stats.st_blocks;
	if (file->stats.st_nlink > parent->nlink_max)
		parent->nlink_max = file->stats.st_nlink;
	set_uidgid(parent, file);
	set_mdate(file);
	if (S_ISBLK(file->stats.st_mode) || S_ISCHR(file->stats.st_mode))
		parent->infos = parent->infos | HAS_BLKCHR;
	else if (file->stats.st_size > parent->size_max)
		parent->size_max = file->stats.st_size;
	if (S_ISLNK(file->stats.st_mode))
	{
		if (!(file->linktarget = ft_strnew(MAXPATHLEN + 1)))
			exit(EXIT_FAILURE);
		readlink(file->path, file->linktarget, MAXPATHLEN);
	}
}
