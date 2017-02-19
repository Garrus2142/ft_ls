/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stats.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 09:05:09 by thugo             #+#    #+#             */
/*   Updated: 2017/02/19 02:10:17 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include "ft_ls.h"

void		file_get_stats(t_params *p, t_file *file)
{
	if (!(p->options & OPT_L_LOW) && file->infos & IS_OPERAND)
	{
		if (stat(file->path, &(file->stats)))
		{
			if (lstat(file->path, &(file->stats)) && !(file->infos & IS_ERROR))
				ls_error(file);
		}
	}
	else
	{
		if (lstat(file->path, &(file->stats)) && !(file->infos & IS_ERROR))
			ls_error(file);
	}
}
