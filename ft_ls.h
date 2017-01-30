/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 18:22:46 by thugo             #+#    #+#             */
/*   Updated: 2017/01/30 18:42:44 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# define OPT_l 1
# define OPT_R 2
# define OPT_a 4
# define OPT_r 8
# define OPT_t 16

typedef struct	s_params
{
	char	options;
	char	**files;
	int		nfiles;
}				t_params;

void	read_args(int argc, char **argv, t_params *params);

#endif
