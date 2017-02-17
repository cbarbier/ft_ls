/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_ftolist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 18:31:14 by cbarbier          #+#    #+#             */
/*   Updated: 2017/02/17 12:06:54 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

char			*ls_handle_dashff(t_ls *ls, t_stat *st, char *filename)
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

static t_list	*read_to_list(t_ls *ls, t_lsarg *data, DIR *directory)
{
	t_dir		*ret;
	t_lsarg		d;
	t_list		*lst;

	lst = 0;
	while ((ret = readdir(directory)) > 0)
	{
		if (!(!(ls->opts & LS_A) && (!ft_strncmp(ret->d_name, ".", 1))))
		{
			bzero(&d, sizeof(t_lsarg));
			d.fullpath = mkpth(data->fullpath, ret->d_name);
			ls_stat(ls, d.fullpath, &(d.fstat));
			d.filename = ft_strdup(ret->d_name);
			d.is_dir = (d.fstat.st_mode & S_IFMT) == S_IFDIR ? 1 : 0;
			if (d.is_dir &&
			!((d.fstat.st_mode & S_IXUSR) && (d.fstat.st_mode & S_IRUSR)))
				d.err = 1;
			ft_lstadd(&lst, ft_lstnew(&d, sizeof(t_lsarg)));
		}
	}
	closedir(directory);
	return (lst);
}

t_list			*ls_ftolist(t_ls *ls, t_lsarg *d)
{
	DIR			*directory;

	if (!(directory = opendir(d->fullpath)))
	{
		d->err = 1;
		return (0);
	}
	return (read_to_list(ls, d, directory));
}
