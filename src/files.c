/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 08:47:05 by thugo             #+#    #+#             */
/*   Updated: 2017/02/14 16:38:21 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include "ft_ls.h"

static int		sort_child(t_list *new, t_list *next, void *param)
{
	if (((t_params *)param)->options & OPT_SORT_TYPE)
	{
		if (((t_file *)new->content)->stats.st_mode & S_IFDIR && !(((t_file *)
			next->content)->stats.st_mode & S_IFDIR))
			return (0);
		else if (!(((t_file *)new->content)->stats.st_mode & S_IFDIR) &&
			((t_file *)next->content)->stats.st_mode & S_IFDIR)
			return (1);
	}
	if (((t_params *)param)->options & OPT_t)
	{
		if (((t_file *)new->content)->stats.st_mtimespec.tv_sec >
				((t_file *)next->content)->stats.st_mtimespec.tv_sec)
			return (((t_params *)param)->options & OPT_r ? 0 : 1);
		else if (((t_file *)new->content)->stats.st_mtimespec.tv_sec <
				((t_file *)next->content)->stats.st_mtimespec.tv_sec)
			return (((t_params *)param)->options & OPT_r ? 1 : 0);
	}
	if (ft_strcmp(((t_file *)new->content)->name,
			((t_file *)next->content)->name) < 0)
		return (((t_params *)param)->options & OPT_r ? 0 : 1);
	return (((t_params *)param)->options & OPT_r ? 1 : 0);
}

static t_file	*dir_add_child(t_params *p, t_file *parent, char *name)
{
	t_file	child;
	char	*fullpath;
	t_list	*new;

	if (!(child.path = ft_strfjoin(ft_strjoin(parent->path, "/"), 1, name, 0)))
		exit(EXIT_FAILURE);
	if (!(child.name = ft_strdup(name)))
		exit(EXIT_FAILURE);
	child.childs = NULL;
	child.errmsg = NULL;
	file_get_stats(p, &child);
	if (!(new = ft_lstnew(&child, sizeof(child))))
		exit(EXIT_FAILURE);
	ft_lstaddsort(&(parent->childs), new, p, sort_child);
	return ((t_file *)new->content);
}

static void		dir_get_childs(t_params *p, t_file *f)
{
	DIR				*dir;
	struct dirent	*dirent;
	t_file			*child;

	if (!(dir = opendir(f->path)))
	{
		f->errmsg = strerror(errno);
		return ;
	}
	while ((dirent = readdir(dir)))
	{
		if (dirent->d_name[0] != '.' || p->options & OPT_a)
		{
			child = dir_add_child(p, f, dirent->d_name);
			if (p->options & OPT_R && dirent->d_type & DT_DIR && ft_strcmp(
				dirent->d_name, ".") != 0 && ft_strcmp(dirent->d_name, "..")
				!= 0)
				dir_get_childs(p, child);
		}
	}
	closedir(dir);
}

void			process_files(t_params *params, t_list **files)
{
	t_file	file;
	t_list	*cur;
	t_list	*new;
	int		i;

	i = -1;
	while (++i < params->nfiles)
	{
		if (!(file.path = ft_strdup(params->files[i])))
			exit(EXIT_FAILURE);
		if (!(file.name = ft_strdup(params->files[i])))
			exit(EXIT_FAILURE);
		file.childs = NULL;
		file.errmsg = NULL;
		file_get_stats(params, &file);
		if (!(new = ft_lstnew(&file, sizeof(file))))
			exit(EXIT_FAILURE);
		ft_lstaddsort(files, new, params, sort_child);
	}
	params->options = params->options & 223;
	cur = *files;
	while (cur)
	{
		if (!((t_file *)cur->content)->errmsg && ((t_file *)cur->content)->
			stats.st_mode & S_IFDIR)
			dir_get_childs(params, (t_file *)cur->content);
		cur = cur->next;
	}
}
