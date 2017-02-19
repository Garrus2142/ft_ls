/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 18:22:46 by thugo             #+#    #+#             */
/*   Updated: 2017/02/19 02:05:46 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# define OPT_L_LOW 1
# define OPT_R 2
# define OPT_A_LOW 4
# define OPT_R_LOW 8
# define OPT_T_LOW 16
# define OPT_SORT_TYPE 32
# define OPT_G 64
# define OPT_1 128

# define IS_OPERAND 1
# define IS_ERROR 2
# define IS_ROOT 4
# define IS_FIRST 8

# define ACC_FILE(cur) ((t_file *)cur->content)

# include <sys/stat.h>
# include "../libft/libft.h"

typedef struct		s_params
{
	char			options;
	char			infos;
	char			**files;
	int				nfiles;
}					t_params;

typedef struct		s_file
{
	char			*path;
	char			*name;
	t_list			*childs;
	struct stat		stats;
	char			infos;
	blkcnt_t		total;
}					t_file;

void				read_args(int argc, char **argv, t_params *params);
void				process_files(t_params *params, t_list **files);
void				file_get_stats(t_params *p, t_file *file);
void				display_file(t_params *p, t_file *file);
void				ls_error(t_file *file);
void				free_file(t_list *elem);
void				get_rights(t_params *p, t_file *file, char *rights);

#endif
