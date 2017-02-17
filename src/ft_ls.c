/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 18:35:00 by thugo             #+#    #+#             */
/*   Updated: 2017/02/17 14:12:25 by thugo            ###   ########.fr       */
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
	t_list	*files;
	t_list	*cur;

	read_args(argc, argv, &params);
	// Debug
	ft_printf("Options: %i\nnfiles: %i\n", params.options, params.nfiles);
	int i = -1;
	while (++i < params.nfiles)
		ft_printf("%s\n", params.files[i]);
	ft_printf("\033[31m<CONTENT>\033[0m\n");
	files = NULL;
	params.options = params.options | OPT_SORT_TYPE;
	process_files(&params, &files);
	/*cur = files;
	while (cur)
	{
		t_file *f = (t_file *)cur->content;
		printf("%s xattr: %d uid: %d size: %lld err: %s\n", f->path, f->xattr, f->stats.st_uid, f->stats.st_size, f->errmsg);
		debug_content(f, 1);
		cur = cur->next;
	}*/
	//free(files);
	ft_tabfree((void ***)&(params.files), params.nfiles);
	return (EXIT_SUCCESS);
}
