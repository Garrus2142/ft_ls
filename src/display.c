/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 12:55:13 by thugo             #+#    #+#             */
/*   Updated: 2017/02/18 16:33:05 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "../libft/libft.h"

void	display_file(t_params *p, t_file *file)
{
	t_list	*cur;

	if (!(file->stats.st_mode & S_IFDIR))
		ft_printf("%s\n", file->path);
	else if (!(file->infos & IS_OPERAND) || p->nfiles > 1)
		ft_printf("%s%s:\n", (file->infos & IS_FIRST) ? "" : "\n", file->path);
	cur = file->childs;
	//ft_printf("Total: %llu\n", file->total);
	while (cur)
	{
		ft_printf("%s\n", ACC_FILE(cur)->name);
		cur = cur->next;
	}
}
