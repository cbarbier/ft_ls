/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 20:48:04 by cbarbier          #+#    #+#             */
/*   Updated: 2017/02/16 18:59:21 by cbarbier         ###   ########.fr       */
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
	else if ((st->st_mode & S_IFMT) == S_IFSOCK)
		ft_strcpy(tmp, "\033[32%*s{no}");
	else if ((st->st_mode & S_IFMT) == S_IFIFO)
		ft_strcpy(tmp, "\033[33%*s{no}");
	else if ((st->st_mode & S_IFMT) == S_IFBLK)
		ft_strcpy(tmp, "\e[106m\033[34m%*s{no}");
	else if ((st->st_mode & S_IFMT) == S_IFCHR)
		ft_strcpy(tmp, "\033[43m\033[34m%*s{no}");
	else if ((st->st_mode & S_IFMT) == S_IFREG && (st->st_mode & S_IXUSR))
		ft_strcpy(tmp, "\033[31m%*s{no}");
	else
		ft_strcpy(tmp, "%*s");
	return (1);
}

int			ls_print_helper(t_ls *ls, t_lsarg *d, int w)
{
	char		tmp[42];
	int			width;

	if (ls->opts & LS_FF)
		d->filename = ls_handle_dashff(ls, &(d->fstat), d->filename);
	if ((ls->opts & LS_GG) && ls_set_color(tmp, &(d->fstat)))
	{
		ft_printf(tmp, 0, d->filename);
		if (w && (width = -w - ft_strlen(d->filename)))
			ft_printf("%*c", width, ' ');
	}
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

static int	ls_print_error(t_ls *ls, t_lsarg *data, t_list *lst)
{
	t_lsarg		*d;

	while (lst)
	{
		d = (t_lsarg *)(lst->content);
		ft_printf("ft_ls: %s: Permission denied\n", d->filename);
		lst = lst->next;
	}
	if (ls)
		ft_printf("ft_ls: %s: Permission denied\n", data->filename);
	return (1);
}

int			ls_print(t_ls *ls, t_lsarg *d, t_list *lst, int depth)
{
	if (d->is_dir && !(!ls->index && !depth) && (ls->index || depth))
		write(1, "\n", 1);
	if (d->is_dir && (ls->fails || ls->files
				|| ls->index || depth || ls->count > 1))
		ft_printf("%s:\n", d->fullpath);
	if (d->is_dir && d->err)
		return (ls_print_error(ls, d, lst));
	if (ls->opts & LS_L)
		ls_print_l(ls, d, lst);
	else if (ls->opts & LS_CC)
		ls_print_c(ls, lst);
	else
		ls_print_classic(ls, lst);
	return (1);
}
