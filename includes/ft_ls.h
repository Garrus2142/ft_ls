/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 18:22:46 by thugo             #+#    #+#             */
/*   Updated: 2017/02/14 15:49:52 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# define OPT_l 1
# define OPT_R 2
# define OPT_a 4
# define OPT_r 8
# define OPT_t 16
# define OPT_SORT_TYPE 32

# include <sys/stat.h>
# include "../libft/libft.h"

typedef struct		s_params
{
	char			options;
	char			**files;
	int				nfiles;
}					t_params;

typedef struct		s_file
{
	char			*path;
	char			*name;
	t_list			*childs;
	char			*errmsg;
	struct stat		stats;
	int				xattr;
}					t_file;

void				read_args(int argc, char **argv, t_params *params);
void				process_files(t_params *params, t_list **files);
void				file_get_stats(t_params *p, t_file *file);

#endif
