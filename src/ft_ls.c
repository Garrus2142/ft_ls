/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 18:35:00 by thugo             #+#    #+#             */
/*   Updated: 2017/02/18 15:23:28 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_ls.h"

void	ls_error(t_file *file)
{
	char	*res;

	file->infos = file->infos | IS_ERROR;
	res = ft_strjoin("ls: ", file->name);
	perror(res);
	free(res);
}

void	free_file(t_list *elem)
{
	free(((t_file *)elem->content)->path);
	free(((t_file *)elem->content)->name);
	free(elem->content);
	free(elem);
}

int		main(int argc, char **argv)
{
	t_params	params;
	t_list		*files;
	t_list		*cur;

	read_args(argc, argv, &params);
	ft_tabsort(params.files, params.nfiles, ft_strcmp);
	files = NULL;
	params.options = params.options | OPT_SORT_TYPE;
	process_files(&params, &files);
	ft_tabfree((void ***)&(params.files), params.nfiles);
	return (EXIT_SUCCESS);
}
