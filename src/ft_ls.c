/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 18:35:00 by thugo             #+#    #+#             */
/*   Updated: 2017/02/17 21:42:41 by thugo            ###   ########.fr       */
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

int		main(int argc, char **argv)
{
	t_params params;
	t_list	*files;
	t_list	*cur;

	read_args(argc, argv, &params);
	files = NULL;
	params.options = params.options | OPT_SORT_TYPE;
	process_files(&params, &files);
	ft_tabfree((void ***)&(params.files), params.nfiles);
	return (EXIT_SUCCESS);
}
