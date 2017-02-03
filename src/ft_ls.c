/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 18:35:00 by thugo             #+#    #+#             */
/*   Updated: 2017/02/03 15:16:39 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_ls.h"

void debug_content(t_file *file, int level)
{
	t_list	*cur;
	cur = file->childs;
	char	*lvl;

	lvl = ft_strnew(level);
	ft_memset(lvl, '\t', level);
	
	while (cur)
	{
		printf("%s%s\n", lvl, ((t_file *)cur->content)->name);
		if (((t_file *)cur->content)->stats.st_mode & S_IFDIR)
			debug_content(((t_file *)cur->content), level + 1);
		cur = cur->next;
	}
}

int		main(int argc, char **argv)
{
	t_params params;
	t_file	*files;
	t_list	*cur;

	read_args(argc, argv, &params);
	// Debug
	ft_printf("Options: %i\nnfiles: %i\n", params.options, params.nfiles);
	int i = -1;
	while (++i < params.nfiles)
		ft_printf("%s\n", params.files[i]);
	ft_printf("<Next>\n");
	if (!(files = (t_file *)malloc(sizeof(t_file) * params.nfiles)))
		exit(EXIT_FAILURE);
	process_files(&params, files);
	i = -1;
	while (++i < params.nfiles)
	{
		printf("%s xattr: %d uid: %d size: %lld err: %s\n", files[i].path, files[i].xattr, files[i].stats.st_uid, files[i].stats.st_size, files[i].errmsg);
		debug_content(files + i, 1);
	}
	free(files);
	ft_tabfree((void ***)&(params.files), params.nfiles);
	return (EXIT_SUCCESS);
}
