/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 17:12:17 by cbarbier          #+#    #+#             */
/*   Updated: 2017/02/10 19:25:22 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

int			ls_core(t_ls *ls, t_lsarg *d, t_list *lst)
{
	static int		depth = 0;	
	t_lsarg			*data;

	ls_sort(ls, &lst);
	ls_print(ls, d, lst, depth++);
	if (!(ls->opts & LS_RR))
		return (1);
	while (lst)
	{
		data = (t_lsarg *)(lst->content);
		if ((data->fstat.st_mode & S_IFDIR) && !data->err
			&& ft_strcmp(data->filename, ".") 
			&& ft_strcmp(data->filename, ".."))
			ls_core(ls, data, ls_ftolist(ls, data->fullpath));
		if ((lst = lst->next))
			write(1, "\n", 1);
	}
	//ft_lstdel(start, );
	return (1);
}
