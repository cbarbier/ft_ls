/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_to_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 15:19:26 by cbarbier          #+#    #+#             */
/*   Updated: 2017/02/12 19:06:33 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static void	add_to_list_args(t_ls *ls, t_lsarg *d)
{
	if ((d->fstat.st_mode & S_IFMT) == S_IFDIR)
		d->is_dir = 1;
	ft_lstpushback(&(ls->args), ft_lstnew(d, sizeof(t_lsarg)));
}

int			ls_arg_to_list(t_ls *ls, char **argv, int start, int end)
{
	t_lsarg		data;

	bzero(&data, sizeof(t_lsarg));
	if (start == end)
	{
		data.filename = ft_strdup(".");
		data.fullpath = ft_strdup(".");
		data.is_dir = 1;
		ls->args = ft_lstnew(&data, sizeof(t_lsarg));
		return (0);
	}
	while (start < end)
	{
		bzero(&data, sizeof(t_lsarg));
		data.filename = ft_strdup(argv[start]);
		data.fullpath = ft_strdup(argv[start]);
		lstat(data.filename, &(data.fstat));
		if (!opendir(argv[start]) && (data.err = errno)
			&& errno != EACCES && errno != ENOTDIR)
			ft_lstpushback(&(ls->fails), ft_lstnew(&data, sizeof(t_lsarg)));
		else
			add_to_list_args(ls, &data);
		start++;
	}
	return (end - start);
}
