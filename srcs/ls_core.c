/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 17:12:17 by cbarbier          #+#    #+#             */
/*   Updated: 2017/02/16 18:47:21 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int			ls_core(t_ls *ls, t_lsarg *d, t_list *lst)
{
	static int		depth = 0;
	t_lsarg			*data;
	t_list			*head;

	ls_sort(ls, &lst);
	ls_print(ls, d, lst, depth++);
	if (!(ls->opts & LS_RR))
	{
		ft_lstdel(&lst, ls_del);
		return (1);
	}
	head = lst;
	while (lst)
	{
		data = (t_lsarg *)(lst->content);
		if (d->is_dir && !d->err
			&& ft_strcmp(data->filename, ".")
			&& ft_strcmp(data->filename, ".."))
			ls_core(ls, data, ls_ftolist(ls, data));
		lst = lst->next;
	}
	ft_lstdel(&head, ls_del);
	return (1);
}
