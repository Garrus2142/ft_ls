/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 08:47:05 by thugo             #+#    #+#             */
/*   Updated: 2017/02/17 17:09:50 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include "ft_ls.h"

static void		free_file(t_list *elem)
{
	free(((t_file *)elem->content)->path);
	free(((t_file *)elem->content)->name);
	if (((t_file *)elem->content)->errmsg)
		free(((t_file *)elem->content)->errmsg);
	free(elem->content);
	free(elem);
}

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
	child.infos = 0;
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
	t_list			*cur;
	t_list			*tmp;

	if (!(dir = opendir(f->path)))
	{
		if (!f->errmsg && !(f->errmsg = ft_strdup(strerror(errno))))
			exit(EXIT_FAILURE);
		display_file(p, f);
		return ;
	}
	while ((dirent = readdir(dir)))
	{
		if (dirent->d_name[0] != '.' || p->options & OPT_a)
			child = dir_add_child(p, f, dirent->d_name);
	}
	closedir(dir);
	display_file(p, f);
	cur = f->childs;
	while (cur)
	{
		if (p->options & OPT_R && ((t_file *)cur->content)->stats.st_mode & S_IFDIR && ft_strcmp(
			((t_file *)cur->content)->name, ".") != 0 && ft_strcmp(((t_file *)cur->content)->name, "..") != 0)
			dir_get_childs(p, (t_file *)cur->content);
		tmp = cur;
		cur = cur->next;
		free_file(tmp);
	}

}

void			process_files(t_params *params, t_list **files)
{
	t_file	file;
	t_list	*cur;
	t_list	*tmp;
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
		file.infos = IS_OPERAND;
		file_get_stats(params, &file);
		if (!(tmp = ft_lstnew(&file, sizeof(file))))
			exit(EXIT_FAILURE);
		ft_lstaddsort(files, tmp, params, sort_child);
	}
	params->options = params->options & (255 ^ OPT_SORT_TYPE);
	cur = *files;
	while (cur)
	{
		if (!((t_file *)cur->content)->errmsg && ((t_file *)cur->content)->
			stats.st_mode & S_IFDIR)
			dir_get_childs(params, (t_file *)cur->content);
		else if (!((t_file *)cur->content)->errmsg)
			display_file(params, (t_file *)cur->content);
		tmp = cur;
		cur = cur->next;
		free_file(tmp);
	}
}
