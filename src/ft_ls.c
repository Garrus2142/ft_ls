/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 18:35:00 by thugo             #+#    #+#             */
/*   Updated: 2017/02/19 02:18:02 by thugo            ###   ########.fr       */
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
	free(((t_file *)elem->content)->path);
	free(((t_file *)elem->content)->name);
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
	params.options = params.options | OPT_SORT_TYPE;
	process_files(&params, &files);
	ft_tabfree((void ***)&(params.files), params.nfiles);
	return (EXIT_SUCCESS);
}
