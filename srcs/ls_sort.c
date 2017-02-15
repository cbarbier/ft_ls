/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 20:48:43 by cbarbier          #+#    #+#             */
/*   Updated: 2017/02/15 18:49:06 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int				ls_cmp_filename(t_list *a, t_list *b)
{
	char *fa;
	char *fb;

	fa = ((t_lsarg *)(a->content))->filename;
	fb = ((t_lsarg *)(b->content))->filename;
	return (ft_strcmp(fa, fb));
}

static int		ls_cmp_size(t_list *a, t_list *b)
{
	off_t		x;
	off_t		y;

	x = ((t_lsarg *)(a->content))->fstat.st_size;
	y = ((t_lsarg *)(b->content))->fstat.st_size;
	if (x == y)
		return (ls_cmp_filename(a, b));
	return (y > x ? 1 : -1);
}

static int		ls_cmp_tdate(t_list *a, t_list *b)
{
	time_t		x;
	time_t		y;

	x = ((t_lsarg *)(a->content))->fstat.st_mtime;
	y = ((t_lsarg *)(b->content))->fstat.st_mtime;
	if (x == y)
		return (ls_cmp_filename(a, b));
	return (y > x ? 1 : -1);
}

void			ls_sort(t_ls *ls, t_list **lst)
{
	int (*f)(t_list *a, t_list *b);

	if (ls->opts & LS_T)
		f = &ls_cmp_tdate;
	else if (ls->opts & LS_SS)
		f = &ls_cmp_size;
	else
		f = &ls_cmp_filename;
	ft_lstsort(*lst, f);
	if (ls->opts & LS_R)
		ft_lstreverse(lst);
}
