/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/19 00:57:26 by thugo             #+#    #+#             */
/*   Updated: 2017/02/19 15:14:05 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/xattr.h>
#include "ft_ls.h"

static void	set_type(t_file *file, char *rights)
{
	if (S_ISBLK(file->stats.st_mode))
		rights[0] = 'b';
	else if (S_ISCHR(file->stats.st_mode))
		rights[0] = 'c';
	else if (S_ISDIR(file->stats.st_mode))
		rights[0] = 'd';
	else if (S_ISLNK(file->stats.st_mode))
		rights[0] = 'l';
	else if (S_ISSOCK(file->stats.st_mode))
		rights[0] = 's';
	else if (S_ISFIFO(file->stats.st_mode))
		rights[0] = 'p';
}

static void	set_rights(t_file *file, char *rights)
{
	if (file->stats.st_mode & S_IRUSR)
		rights[1] = 'r';
	if (file->stats.st_mode & S_IWUSR)
		rights[2] = 'w';
	if (file->stats.st_mode & S_ISUID)
		rights[3] = (file->stats.st_mode & S_IXUSR) ? 's' : 'S';
	else if (file->stats.st_mode & S_IXUSR)
		rights[3] = 'x';
	if (file->stats.st_mode & S_IRGRP)
		rights[4] = 'r';
	if (file->stats.st_mode & S_IWGRP)
		rights[5] = 'w';
	if (file->stats.st_mode & S_ISGID)
		rights[6] = (file->stats.st_mode & S_IXGRP) ? 's' : 'S';
	else if (file->stats.st_mode & S_IXGRP)
		rights[6] = 'x';
	if (file->stats.st_mode & S_IROTH)
		rights[7] = 'r';
	if (file->stats.st_mode & S_IWOTH)
		rights[8] = 'w';
	if (file->stats.st_mode & S_ISVTX)
		rights[9] = (file->stats.st_mode & S_IXOTH) ? 't' : 'T';
	else if (file->stats.st_mode & S_IXOTH)
		rights[9] = 'x';
}

static void	set_attr(t_file *file, char *rights)
{
	if (listxattr(file->path, NULL, 0, XATTR_NOFOLLOW) > 0)
		rights[10] = '@';
}

void		get_rights(t_params *p, t_file *file, char *rights)
{
	ft_memset(rights, '-', 10);
	ft_memset(rights + 10, '\0', 2);
	set_type(file, rights);
	set_rights(file, rights);
	set_attr(file, rights);
}
