/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_ftolist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 18:31:14 by cbarbier          #+#    #+#             */
/*   Updated: 2017/02/10 13:15:32 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

static t_list	*read_to_list(t_ls *ls, char *filename, DIR	*directory)
{
	t_dir		*ret;
	t_lsarg		data;
	t_list		*lst;

	lst = 0;
	while ((ret = readdir(directory)))
	{
		if (!(!(ls->opts & LS_A) && (!ft_strncmp(ret->d_name, ".", 1))))
		{
			bzero(&data, sizeof(t_lsarg));
			data.filename = ft_strdup(ret->d_name);
			data.fullpath = mkpth(filename, ret->d_name);
			lstat(data.fullpath, &(data.fstat));
			ft_lstadd(&lst, ft_lstnew(&data, sizeof(t_lsarg)));
		}
	}
	return (lst);
}

t_list		*ls_ftolist(t_ls *ls, char	*filename)
{
	DIR			*directory;
	t_lsarg		data;

	bzero(&data, sizeof(t_lsarg));
	data.filename = ft_strdup(filename);
	data.fullpath = ft_strdup(filename);
	lstat(filename, &(data.fstat));
	if (!((data.fstat.st_mode & S_IFMT) == S_IFDIR))
		return (ft_lstnew(&data, sizeof(t_lsarg)));
	if (!(directory = opendir(filename)))
	{
		data.err = errno;
		return (ft_lstnew(&data, sizeof(t_lsarg)));
	}
	return (read_to_list(ls, filename, directory));
}
