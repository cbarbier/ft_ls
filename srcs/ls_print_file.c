/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 20:48:04 by cbarbier          #+#    #+#             */
/*   Updated: 2017/02/09 17:59:25 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"


int		ls_print_file(t_ls *ls, t_lsarg *d, t_list *lst)
{
	t_lsarg	*data;

	if (ls->count > 1 && d->is_dir && (d->fstat.st_mode & S_IFDIR))
		ft_printf("%s:\n", d->filename);
	if (ls->opts & LS_L)
		return (ls_print_l(lst));
	while (lst)
	{
		data = (t_lsarg *)(lst->content);
		if (data->err)
			ft_printf("ft_ls: %s: %s\n", data->filename, strerror(data->err));
		else
			ft_printf("%s\n", data->filename);
		lst = lst->next;
	}
	return (1);
}
