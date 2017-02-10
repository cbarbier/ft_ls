/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 20:48:04 by cbarbier          #+#    #+#             */
/*   Updated: 2017/02/10 19:26:39 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

static	int	ls_print_helper(t_ls *ls, t_lsarg *data)
{
	if (ls->args)
		ft_printf("%s\n", data->filename);
	return (1);
}


static int	ls_print_classic(t_ls *ls, t_list *lst)
{
	t_lsarg		*data;

	while (lst)
	{
		data = (t_lsarg *)(lst->content);
		ls_print_helper(ls, data);
		lst = lst->next;
	}
	return (1);
}

int			ls_print(t_ls *ls, t_lsarg *d, t_list *lst, int depth)
{
	if (ls->count > 1 || depth)
		ft_printf("%s:\n", d->fullpath);
	if (d->err)
		ft_printf("ft_ls: %s: %s\n", d->filename, strerror(d->err));
	else if (ls->opts & LS_L)
		ls_print_l(lst);
	else
		ls_print_classic(ls, lst);
	return (1);
}

