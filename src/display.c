/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 12:55:13 by thugo             #+#    #+#             */
/*   Updated: 2017/02/19 03:50:14 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "../libft/libft.h"

// Afficher l'annee de modification si la est plus recente ou vielle de 6 mois a la place de l'heure
// Si file type == Block special or Charactere special, afficher le minor et major a la place de size
// Si c'est un liens alors on affiche la cible -> 
// Voir les cas des other permission (x, S, t)

static void	print_long(t_params *p, t_file *file)
{
	char rights[12];

	get_rights(p, file, rights);
	ft_printf("%-11s %*lu %s\n", rights, file->nlink_max, file->stats.st_nlink, file->name);
}

void	display_file(t_params *p, t_file *file)
{
	t_list	*cur;

	if (!(file->stats.st_mode & S_IFDIR))
		ft_printf("%s\n", file->path);
	else if (!(file->infos & IS_OPERAND) || p->nfiles > 1)
		ft_printf("%s%s:\n", (file->infos & IS_FIRST) ? "" : "\n", file->path);
	if (p->options & OPT_L_LOW)
		file->nlink_max = ft_sizelong(file->nlink_max);
	cur = file->childs;
	//ft_printf("Total: %llu\n", file->total);
	//ft_printf("nlink_max: %lu\n", file->nlink_max);
	while (cur)
	{
		if (p->options & OPT_L_LOW)
		{
			ACC_FILE(cur)->nlink_max = file->nlink_max;
			print_long(p, ACC_FILE(cur));
		}
		else
			ft_printf("%s\n", ACC_FILE(cur)->name);
		cur = cur->next;
	}
}
