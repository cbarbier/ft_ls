/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 20:48:04 by cbarbier          #+#    #+#             */
/*   Updated: 2017/02/13 12:07:25 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static int	ls_set_color(char *tmp, t_stat *st)
{
	if ((st->st_mode & S_IFMT) == S_IFDIR)
		ft_strcpy(tmp, "{blu}%s%s{no}");
	else if ((st->st_mode & S_IFMT) == S_IFLNK)
		ft_strcpy(tmp, "\033[35m%s%s{no}");
	else if (st->st_mode & S_IXUSR)
		ft_strcpy(tmp, "{red}%s%s{no}");
	else
		ft_strcpy(tmp, "%s%s");
	return (1);
}

static int	ls_print_helper(t_ls *ls, t_lsarg *d, char *br)
{
	char tmp[25];

	ft_bzero(tmp, 25 * sizeof(char));
	if (d->err)
		ft_printf("ft_ls: %s: %s\n", d->filename, strerror(d->err));
	else if ((ls->opts & LS_GG) && ls_set_color(tmp, &(d->fstat)))
		ft_printf(tmp, d->filename, br);
	else
		ft_printf("%s%s", d->filename, br);
	return (1);
}

static int	ls_print_classic(t_ls *ls, t_list *lst)
{
	t_lsarg		*data;

	while (lst)
	{
		data = (t_lsarg *)(lst->content);
		ls_print_helper(ls, data, "\n");
		lst = lst->next;
	}
	return (1);
}

int			ls_print(t_ls *ls, t_lsarg *d, t_list *lst, int depth)
{
	if (d->is_dir && (ls->index || depth))
		write(1, "\n", 1);
	if (d->is_dir && (ls->index || depth))
		ft_printf("%s:\n", d->fullpath);
	if (ls->opts & LS_L)
		ls_print_l(ls, d, lst);
	else
		ls_print_classic(ls, lst);
	return (1);
}
