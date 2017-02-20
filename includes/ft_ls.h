/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 18:22:46 by thugo             #+#    #+#             */
/*   Updated: 2017/02/20 10:51:51 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# define OPT_L_LOW 1
# define OPT_R 2
# define OPT_A_LOW 4
# define OPT_R_LOW 8
# define OPT_T_LOW 16
# define OPT_G 32
# define OPT_1 64

# define HAS_BLKCHR 1
# define IS_OPERAND 2
# define IS_ERROR 4
# define IS_ROOT 8
# define IS_FIRST 16

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
	char			*pw_name;
	char			*gr_name;
	struct stat		stats;
	char			infos;
	blkcnt_t		total;
	char			*linktarget;
	char			mtime[14];
	nlink_t			nlink_max;
	int				n_pw_name;
	int				n_gr_name;
	off_t			size_max;
}					t_file;

void				read_args(int argc, char **argv, t_params *params);
void				process_files(t_params *params, t_list **files);
int					file_get_stats(t_params *p, t_file *file);
void				file_get_long_stats(t_file *parent, t_file *file);
void				display_file(t_params *p, t_file *file);
void				ls_error(t_file *file);
void				free_file(t_list *elem);
void				get_rights(t_params *p, t_file *file, char *rights);

#endif
