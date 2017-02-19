/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 12:55:13 by thugo             #+#    #+#             */
/*   Updated: 2017/02/19 18:17:33 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/types.h>
#include "ft_ls.h"

// Afficher l'annee de modification si la est plus recente ou vielle de 6 mois a la place de l'heure
// Si file type == Block special or Charactere special, afficher le minor et major a la place de size
// Si c'est un liens alors on affiche la cible -> 
// Voir les cas des other permission (x, S, t)

static void	print_long(t_params *p, t_file *par, t_file *file)
{
	char	rights[12];
	char	*pwname;
	char	*grname;

	if (!(pwname = file->pw_name ? file->pw_name : ft_itoa(file->stats.st_uid)))
		exit(EXIT_FAILURE);
	if (!(grname = file->gr_name ? file->gr_name : ft_itoa(file->stats.st_gid)))
		exit(EXIT_FAILURE);
	get_rights(p, file, rights);
	ft_printf("%-11s %*lu %-*s  %-*s", rights, par->nlink_max, file->stats.st_nlink,
		 par->n_pw_name, pwname, par->n_gr_name, grname, par->size_max);
	if (S_ISBLK(file->stats.st_mode) || S_ISCHR(file->stats.st_mode))
	{
		ft_printf("  %3lu, %3lu", major(file->stats.st_rdev),
			minor(file->stats.st_rdev));
	}
	else
		ft_printf("  %*lu", par->size_max + ((par->infos & HAS_BLKCHR) * 7), file->stats.st_size);
	ft_printf(" %s\n", file->name);
	free(pwname);
	free(grname);
}

void	display_file(t_params *p, t_file *file)
{
	t_list	*cur;

	if (!(file->stats.st_mode & S_IFDIR) && !(p->options & OPT_L_LOW))
		ft_printf("%s\n", file->path);
	else if (!(file->infos & IS_OPERAND) || p->nfiles > 1)
		ft_printf("%s%s:\n", (file->infos & IS_FIRST) ? "" : "\n", file->path);
	if (p->options & OPT_L_LOW)
	{
		file->nlink_max = ft_sizelong(file->nlink_max);
		file->size_max = ft_sizelong(file->size_max);
		if (file->infos & IS_OPERAND && !(S_ISDIR(file->stats.st_mode)))
			print_long(p, file, file);
	}
	cur = file->childs;
	//ft_printf("Total: %llu\n", file->total);
	//ft_printf("nlink_max: %lu\n", file->nlink_max);
	while (cur)
	{
		if (p->options & OPT_L_LOW)
			print_long(p, file, ACC_FILE(cur));
		else
			ft_printf("%s\n", ACC_FILE(cur)->name);
		cur = cur->next;
	}
}
