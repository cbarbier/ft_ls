/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 17:12:17 by cbarbier          #+#    #+#             */
/*   Updated: 2017/02/07 19:39:52 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

int			ls_core(t_ls *ls, char	*f, t_list *lst)
{	
	t_lsarg	*data;

	ls_sort(ls, &lst);
	ls_print_file(ls, f, lst);
	if (!(ls->opts & LS_RR))
		return (1);
	while (lst)
	{
		data = (t_lsarg *)(lst->content);
		if ((data->fstat.st_mode & S_IFDIR) && !data->err
			&& ft_strcmp(data->filename, ".") 
			&& ft_strcmp(data->filename, ".."))
			ls_core(ls, data->fullpath, ls_ftolist(ls, data->fullpath));
		lst = lst->next;
	}
	//ft_lstdel(start, );
	return (1);
}
