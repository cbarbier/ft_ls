/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 20:48:43 by cbarbier          #+#    #+#             */
/*   Updated: 2017/02/07 20:27:49 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

static int		ls_cmp_filename(t_list *a, t_list *b)
{
	char *fa;
	char *fb;

	fa = ((t_lsarg *)(a->content))->filename;
	fb = ((t_lsarg *)(b->content))->filename;
	return (ft_strcmp(fa, fb));
}

static int		ls_cmp_tdate(t_list *a, t_list *b)
{
	struct timespec		x;
	struct timespec		y;

	x = ((t_lsarg *)(a->content))->fstat.st_mtimespec;
	y = ((t_lsarg *)(b->content))->fstat.st_mtimespec;
	if (x.tv_sec == y.tv_sec)
		return (y.tv_nsec > x.tv_nsec ? 1 : (y.tv_nsec < x.tv_nsec ? -1 : 0));
	return (y.tv_sec > x.tv_sec ? 1 : -1);
}


static int		ls_cmp_udate(t_list *a, t_list *b)
{
	struct timespec		x;
	struct timespec		y;

	x = ((t_lsarg *)(a->content))->fstat.st_atimespec;
	y = ((t_lsarg *)(b->content))->fstat.st_atimespec;
	if (x.tv_sec == y.tv_sec)
		return (y.tv_nsec > x.tv_nsec ? 1 : (y.tv_nsec < x.tv_nsec ? -1 : 0));
	return (y.tv_sec > x.tv_sec ? 1 : -1);
}

void			ls_sort(t_ls *ls, t_list **lst)
{
	int (*f)(t_list *a, t_list *b);

	if (ls->opts & LS_T)
		f = &ls_cmp_tdate;
	else if (ls->opts & LS_U)
		f = &ls_cmp_udate;
	else
		f = &ls_cmp_filename;
	ft_lstsort(*lst, f);
	if (ls->opts & LS_R)
		ft_lstreverse(lst);
}
