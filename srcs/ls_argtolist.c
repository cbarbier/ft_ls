/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_to_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 15:19:26 by cbarbier          #+#    #+#             */
/*   Updated: 2017/02/16 08:16:48 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static void	add_to_list_args(t_ls *ls, t_lsarg *d)
{
	if ((d->fstat.st_mode & S_IFMT) == S_IFDIR)
		d->is_dir = 1;
	ft_lstpushback(&(ls->args), ft_lstnew(d, sizeof(t_lsarg)));
}

static int	default_list(t_ls *ls, t_lsarg *data)
{
	bzero(data, sizeof(t_lsarg));
	data->filename = ft_strdup(".");
	data->fullpath = ft_strdup(".");
	data->is_dir = 1;
	ls->args = ft_lstnew(data, sizeof(t_lsarg));
	return (0);
}

int			ls_arg_to_list(t_ls *ls, char **argv, int start, int end)
{
	t_lsarg		data;
	DIR			*dir;

	if (start == end)
		return (default_list(ls, &data));
	while (start < end)
	{
		bzero(&data, sizeof(t_lsarg));
		data.filename = ft_strdup(argv[start]);
		data.fullpath = ft_strdup(argv[start]);
		ls_stat(ls, data.filename, &(data.fstat));
		if (!(dir = opendir(argv[start]))
			&& errno != EACCES && errno != ENOTDIR)
		{
			data.err = errno;
			ft_lstpushback(&(ls->fails), ft_lstnew(&data, sizeof(t_lsarg)));
		}
		else
			add_to_list_args(ls, &data);
		if (dir)
			closedir(dir);
		start++;
	}
	return (end - start);
}
