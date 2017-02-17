/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 12:55:13 by thugo             #+#    #+#             */
/*   Updated: 2017/02/17 18:40:56 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "../libft/libft.h"

void	display_file(t_params *p, t_file *file)
{
	t_list	*cur;
	ft_printf("\n%s:\n", file->path);
	cur = file->childs;
	while (cur)
	{
		ft_printf("%s\n", ((t_file *)cur->content)->name);
		cur = cur->next;
	}
}
