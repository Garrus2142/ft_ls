/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stats.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 09:05:09 by thugo             #+#    #+#             */
/*   Updated: 2017/02/17 17:01:42 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <sys/xattr.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include "ft_ls.h"

void		file_get_stats(t_params *p, t_file *file)
{
	int	ret;

	if (!(p->options & OPT_l) && file->infos & IS_OPERAND)
	{
		if (stat(file->path, &(file->stats)) != 0 && !file->errmsg)
		{
			if (!(file->errmsg = ft_strdup(strerror(errno))))
				exit(EXIT_FAILURE);
		}
	}
	else
	{
		if (lstat(file->path, &(file->stats)) != 0 && !file->errmsg)
		{
			if (!(file->errmsg = ft_strdup(strerror(errno))))
				exit(EXIT_FAILURE);
		}
	}
	if ((ret = listxattr(file->path, NULL, 0, XATTR_NOFOLLOW)) > 0)
		file->xattr = 1;
	else
		file->xattr = 0;
}
