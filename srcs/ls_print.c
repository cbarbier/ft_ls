/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 20:48:04 by cbarbier          #+#    #+#             */
/*   Updated: 2017/02/14 14:51:51 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static int	ls_set_color(char *tmp, t_stat *st)
{
	ft_bzero(tmp, 42 * sizeof(char));
	if ((st->st_mode & S_IFMT) == S_IFDIR)
		ft_strcpy(tmp, "\e[96m%*s{no}");
	else if ((st->st_mode & S_IFMT) == S_IFLNK)
		ft_strcpy(tmp, "\033[35m%*s{no}");
	else if ((st->st_mode & S_IFMT) == S_IFBLK)
		ft_strcpy(tmp, "\e[106m\033[34m%*s{no}");
	else if ((st->st_mode & S_IFMT) == S_IFCHR)
		ft_strcpy(tmp, "\033[43m\033[34m%*s{no}");
	else if (st->st_mode & S_IXUSR)
		ft_strcpy(tmp, "{red}%*s{no}");
	else
		ft_strcpy(tmp, "%*s");
	return (1);
}

int			ls_print_helper(t_ls *ls, t_lsarg *d, int w)
{
	char		tmp[42];

	if (d->err)
		return (ft_printf("ft_ls: %s: %s", d->filename, strerror(d->err)));
	if ((ls->opts & LS_GG) && ls_set_color(tmp, &(d->fstat)))
		ft_printf(tmp, w, d->filename);
	else
		ft_printf("%*s", w, d->filename);
	return (1);
}

static int	ls_print_classic(t_ls *ls, t_list *lst)
{
	t_lsarg		*data;

	while (lst)
	{
		data = (t_lsarg *)(lst->content);
		ls_print_helper(ls, data, 0);
		lst = lst->next;
		write(1, "\n", 1);
	}
	return (1);
}

int			ls_print(t_ls *ls, t_lsarg *d, t_list *lst, int depth)
{
	if (d->is_dir && !(!ls->index && !depth) && (ls->index || depth))
		write(1, "\n", 1);
	if (d->is_dir && (ls->index || depth || ls->count > 1))
		ft_printf("%s:\n", d->fullpath);
	if (ls->opts & LS_L)
		ls_print_l(ls, d, lst);
	else if (ls->opts & LS_C)
		ls_print_c(ls, lst);
	else
		ls_print_classic(ls, lst);
	return (1);
}
