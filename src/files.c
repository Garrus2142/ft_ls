/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 08:47:05 by thugo             #+#    #+#             */
/*   Updated: 2017/02/20 09:55:30 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include "ft_ls.h"

static int		sort_child(t_list *new, t_list *next, void *param)
{
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
	t_list	*new;

	if (name[0] == '.' && !(p->options & OPT_A_LOW))
		return ;
	ft_bzero(&child, sizeof(t_file));
	if (!(child.path = ft_strfjoin(ft_strjoin(parent->path,
			(parent->infos & IS_ROOT) ? "" : "/"), 1, name, 0)))
		exit(EXIT_FAILURE);
	if (!(child.name = ft_strdup(name)))
		exit(EXIT_FAILURE);
	file_get_stats(p, &child);
	if (p->options & OPT_L_LOW)
		file_get_long_stats(parent, &child);
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
		if (p->options & OPT_R && S_ISDIR(ACC_FILE(cur)->stats.st_mode) &&
	ft_strcmp(ACC_FILE(cur)->name, ".") && ft_strcmp(ACC_FILE(cur)->name, ".."))
			dir_get_childs(p, (t_file *)cur->content);
		cur = cur->next;
		free_file(tmp);
	}
	f->childs = NULL;
}

static void		setup_operand(t_params *params, t_file *nodirs, t_list **files)
{
	t_file	file;
	t_list	*new;
	int		i;

	ft_bzero(nodirs, sizeof(t_file));
	i = -1;
	while (++i < params->nfiles)
	{
		ft_bzero(&file, sizeof(t_file));
		file.path = ft_strdup(params->files[i]);
		if (!file.path || !(file.name = ft_strdup(params->files[i])))
			exit(EXIT_FAILURE);
		file.infos = (IS_OPERAND | (!ft_strcmp(file.path, "/") ? IS_ROOT : 0));
		if (file_get_stats(params, &file))
		{
			if (!(new = ft_lstnew(&file, sizeof(file))))
				exit(EXIT_FAILURE);
			if (params->options & OPT_L_LOW && !S_ISDIR(file.stats.st_mode))
				file_get_long_stats(nodirs, ACC_FILE(new));
			if (!S_ISDIR(file.stats.st_mode))
				ft_lstaddsort(&(nodirs->childs), new, params, sort_child);
			else
				ft_lstaddsort(files, new, params, sort_child);
		}
	}
}

void			process_files(t_params *params, t_list **files)
{
	t_file	nodirs;
	t_list	*cur;
	t_list	*tmp;

	setup_operand(params, &nodirs, files);
	if (nodirs.childs)
	{
		if (!(tmp = ft_lstnew(&nodirs, sizeof(t_file))))
			exit(EXIT_FAILURE);
		ft_lstadd(files, tmp);
	}
	cur = *files;
	if (cur)
		ACC_FILE(cur)->infos = ACC_FILE(cur)->infos | IS_FIRST;
	while ((tmp = cur))
	{
		free(ACC_FILE(cur)->name);
		ACC_FILE(cur)->name = ft_path_getfile(ACC_FILE(cur)->path);
		if (S_ISDIR(ACC_FILE(cur)->stats.st_mode))
			dir_get_childs(params, ACC_FILE(cur));
		else
			display_file(params, ACC_FILE(cur));
		cur = cur->next;
		free_file(tmp);
	}
}
