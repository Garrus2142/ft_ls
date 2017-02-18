/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 08:47:05 by thugo             #+#    #+#             */
/*   Updated: 2017/02/18 17:11:22 by thugo            ###   ########.fr       */
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
		if (ACC_FILE(new)->stats.st_mode & S_IFDIR &&
				!(ACC_FILE(next)->stats.st_mode & S_IFDIR))
			return (0);
		else if (!(ACC_FILE(new)->stats.st_mode & S_IFDIR) &&
				ACC_FILE(next)->stats.st_mode & S_IFDIR)
			return (1);
	}
	if (((t_params *)param)->options & OPT_T_LOW)
	{
		if (ACC_FILE(new)->stats.st_mtimespec.tv_sec >
				ACC_FILE(next)->stats.st_mtimespec.tv_sec)
			return (((t_params *)param)->options & OPT_R_LOW ? 0 : 1);
		else if (ACC_FILE(new)->stats.st_mtimespec.tv_sec <
				ACC_FILE(next)->stats.st_mtimespec.tv_sec)
			return (((t_params *)param)->options & OPT_R_LOW ? 1 : 0);
	}
	if (ft_strcmp(ACC_FILE(new)->name, ACC_FILE(next)->name) < 0)
		return (((t_params *)param)->options & OPT_R_LOW ? 0 : 1);
	return (((t_params *)param)->options & OPT_R_LOW ? 1 : 0);
}

static void		dir_add_child(t_params *p, t_file *parent, char *name)
{
	t_file	child;
	char	*fullpath;
	t_list	*new;

	if (name[0] == '.' && !(p->options & OPT_A_LOW))
		return ;
	if (!(child.path = ft_strfjoin(ft_strjoin(parent->path,
			(parent->infos & IS_ROOT) ? "" : "/"), 1, name, 0)))
		exit(EXIT_FAILURE);
	if (!(child.name = ft_strdup(name)))
		exit(EXIT_FAILURE);
	child.childs = NULL;
	child.infos = 0;
	child.total = 0;
	file_get_stats(p, &child);
	parent->total += child.stats.st_blocks;
	if (!(new = ft_lstnew(&child, sizeof(child))))
		exit(EXIT_FAILURE);
	ft_lstaddsort(&(parent->childs), new, p, sort_child);
}

static void		dir_get_childs(t_params *p, t_file *f)
{
	DIR				*dir;
	struct dirent	*dirent;
	t_list			*cur;
	t_list			*tmp;

	if (!(dir = opendir(f->path)))
	{
		display_file(p, f);
		ls_error(f);
		return ;
	}
	while ((dirent = readdir(dir)))
		dir_add_child(p, f, dirent->d_name);
	closedir(dir);
	display_file(p, f);
	cur = f->childs;
	while ((tmp = cur))
	{
		if (p->options & OPT_R && ACC_FILE(cur)->stats.st_mode & S_IFDIR &&
				ft_strcmp(ACC_FILE(cur)->name, ".") != 0 &&
				ft_strcmp(ACC_FILE(cur)->name, "..") != 0)
			dir_get_childs(p, (t_file *)cur->content);
		cur = cur->next;
		free_file(tmp);
	}
}

static void		setup_operand(t_params *params, t_list **files)
{
	t_file	file;
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
		file.infos = (IS_OPERAND | (!ft_strcmp(file.path, "/") ? IS_ROOT : 0));
		file.total = 0;
		file_get_stats(params, &file);
		if (!(file.infos & IS_ERROR))
		{
			if (!(tmp = ft_lstnew(&file, sizeof(file))))
				exit(EXIT_FAILURE);
			ft_lstaddsort(files, tmp, params, sort_child);
		}
	}
}

void			process_files(t_params *params, t_list **files)
{
	t_list	*cur;
	t_list	*tmp;

	setup_operand(params, files);
	params->options = params->options & (255 ^ OPT_SORT_TYPE);
	cur = *files;
	if (cur)
		ACC_FILE(cur)->infos = ACC_FILE(cur)->infos | IS_FIRST;
	while ((tmp = cur))
	{
		free(ACC_FILE(cur)->name);
		ACC_FILE(cur)->name = ft_path_getfile(ACC_FILE(cur)->path);
		if (ACC_FILE(cur)->stats.st_mode & S_IFDIR)
			dir_get_childs(params, (t_file *)cur->content);
		else
			display_file(params, (t_file *)cur->content);
		cur = cur->next;
		free_file(tmp);
	}
}
