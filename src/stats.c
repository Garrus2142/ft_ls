/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stats.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 09:05:09 by thugo             #+#    #+#             */
/*   Updated: 2017/02/03 09:57:48 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <sys/xattr.h>
#include <errno.h>
#include <string.h>
#include "ft_ls.h"

void		file_get_stats(t_file *file)
{
	int	ret;

	if (lstat(file->path, &(file->stats)) != 0)
		file->errmsg = strerror(errno);
	if ((ret = listxattr(file->path, NULL,0, XATTR_NOFOLLOW)) == -1)
		file->errmsg = strerror(errno);
	file->xattr = ret > 0 ? 1 : 0;
}
