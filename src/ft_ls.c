/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 18:35:00 by thugo             #+#    #+#             */
/*   Updated: 2017/02/20 08:44:35 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "ft_ls.h"

void		ls_error(t_file *file)
{
	char	*res;

	file->infos = file->infos | IS_ERROR;
	res = ft_strjoin("ls: ", file->name);
	perror(res);
	free(res);
}

void		free_file(t_list *elem)
{
	t_list	*cur;
	t_list	*tmp;

	free(ACC_FILE(elem)->path);
	free(ACC_FILE(elem)->name);
	if (ACC_FILE(elem)->linktarget)
		free(ACC_FILE(elem)->linktarget);
	cur = ACC_FILE(elem)->childs;
	while ((tmp = cur))
	{
		cur = cur->next;
		free_file(tmp);
	}
	free(elem->content);
	free(elem);
}

static void	check_empty(t_params *p)
{
	int	i;

	i = -1;
	while (++i < p->nfiles)
	{
		if (!ft_strlen(p->files[i]))
		{
			ft_putstr_fd("ls: fts_open: No such file or directory\n",
				STDERR_FILENO);
			exit(EXIT_FAILURE);
		}
	}
}

int			main(int argc, char **argv)
{
	t_params	params;
	t_list		*files;
	t_list		*cur;

	read_args(argc, argv, &params);
	check_empty(&params);
	ft_tabsort(params.files, params.nfiles, ft_strcmp);
	files = NULL;
	process_files(&params, &files);
	ft_tabfree((void ***)&(params.files), params.nfiles);
	return (EXIT_SUCCESS);
}
