/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_to_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 15:19:26 by cbarbier          #+#    #+#             */
/*   Updated: 2017/02/09 18:09:02 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

int			ls_arg_to_list(t_ls *ls, char **argv,  int start, int end)
{
	t_lsarg		data;

	bzero(&data, sizeof(t_lsarg));
	if (start == end)
	{
		data.filename = ft_strdup(".");
		ls->args = ft_lstnew(&data, sizeof(t_lsarg));
		return (1);
	}
	while (start < end)
	{
		bzero(&data, sizeof(t_lsarg));
		data.filename = ft_strdup(argv[start]);
		lstat(data.filename, &(data.fstat));
		if (!opendir(argv[start]) && (data.err = errno)
			&& errno != EACCES && errno != ENOTDIR)
			ft_lstpushback(&(ls->fails), ft_lstnew(&data, sizeof(t_lsarg)));
		else
			ft_lstpushback(&(ls->args), ft_lstnew(&data, sizeof(t_lsarg)));
		start++;
	}
	return (end - start);
}
