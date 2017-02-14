/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_ftolist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 18:31:14 by cbarbier          #+#    #+#             */
/*   Updated: 2017/02/14 18:34:01 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static char		*ls_handle_dashff(t_ls *ls, t_stat *st, char *filename)
{
	if (!(ls->opts & LS_FF))
		return (ft_strdup(filename));
	if ((st->st_mode & S_IFMT) == S_IFDIR)
		return (ft_strjoinzfree(filename, "/", 0));
	else if ((st->st_mode & S_IFMT) == S_IFLNK)
		return (ft_strjoinzfree(filename, "@", 0));
	else if (st->st_mode & S_IXUSR)
		return (ft_strjoinzfree(filename, "*", 0));
	else if ((st->st_mode & S_IFMT) == S_IFSOCK)
		return (ft_strjoinzfree(filename, "=", 0));
	else if ((st->st_mode & S_IFMT) == S_IFWHT)
		return (ft_strjoinzfree(filename, "%", 0));
	else if ((st->st_mode & S_IFMT) == S_IFIFO)
		return (ft_strjoinzfree(filename, "|", 0));
	return (ft_strdup(filename));
}

static t_list	*read_to_list(t_ls *ls, char *filename, DIR *directory)
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
			data.fullpath = mkpth(filename, ret->d_name);
			lstat(data.fullpath, &(data.fstat));
			data.filename = ls_handle_dashff(ls, &(data.fstat), ret->d_name);
			data.is_dir = (data.fstat.st_mode & S_IFMT) == S_IFDIR ? 1 : 0;
			ft_lstadd(&lst, ft_lstnew(&data, sizeof(t_lsarg)));
		}
	}
	closedir(directory);
	return (lst);
}

t_list			*ls_ftolist(t_ls *ls, char *filename)
{
	DIR			*directory;
	t_lsarg		data;
	char			*tmp;

	bzero(&data, sizeof(t_lsarg));
	if ((tmp = ft_strrchr(filename, '/')) && *(++tmp))
		data.filename = ft_strdup(tmp);
	else
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
	ft_strdel(&(data.filename));
	ft_strdel(&(data.fullpath));
	return (read_to_list(ls, filename, directory));
}
