/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print_l.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 10:06:07 by cbarbier          #+#    #+#             */
/*   Updated: 2017/02/15 13:00:43 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static void	print_date(char *tmp, time_t fdate)
{
	time_t	curtime;
	char	*snow;
	char	*sfil;

	time(&curtime);
	snow = ctime(&curtime);
	sfil = ctime(&fdate);
	bzero(tmp, 42 * sizeof(char));
	ft_strncat(tmp, sfil + 4, 3);
	ft_strcat(tmp, (ft_isdigit(sfil[9]) ? " " : "  "));
	ft_strncat(tmp, sfil + 8, ft_isdigit(sfil[9]) ? 2 : 1);
	ft_strcat(tmp, " ");
	if (!(curtime - fdate > 15778458 || fdate - curtime > 3600))
		ft_strncat(tmp, sfil + 11, 5);
	else
		ft_strncat(ft_strcat(tmp, " "), sfil + 20, 4);
	ft_printf("%s ", tmp);
}

static int	set_lns(t_list *lst, int *thogsmm)
{
	int		res;
	t_stat	*st;

	bzero(thogsmm, 7 * sizeof(int));
	while (lst)
	{
		st = &(((t_lsarg *)(lst->content))->fstat);
		thogsmm[0] += st->st_blocks;
		if ((res = ft_nblen(st->st_nlink)) > thogsmm[1])
			thogsmm[1] = res;
		if ((res = ft_strlen(getpwuid(st->st_uid)->pw_name)) > thogsmm[2])
			thogsmm[2] = res;
		if ((res = ft_strlen(getgrgid(st->st_gid)->gr_name)) > thogsmm[3])
			thogsmm[3] = res;
		if ((res = ft_nblen(st->st_size)) > thogsmm[4])
			thogsmm[4] = res;
		ls_set_lns_min_maj(thogsmm, st);
		lst = lst->next;
	}
	if (thogsmm[4] < (res = thogsmm[5] + thogsmm[6] + 2))
		thogsmm[4] = res;
	return (1);
}

static char	set_typeoffile(t_stat *st)
{
	if ((st->st_mode & S_IFMT) == S_IFIFO)
		return ('p');
	else if ((st->st_mode & S_IFMT) == S_IFCHR)
		return ('c');
	else if ((st->st_mode & S_IFMT) == S_IFDIR)
		return ('d');
	else if ((st->st_mode & S_IFMT) == S_IFBLK)
		return ('b');
	else if ((st->st_mode & S_IFMT) == S_IFREG)
		return ('-');
	else if ((st->st_mode & S_IFMT) == S_IFLNK)
		return ('l');
	else if ((st->st_mode & S_IFMT) == S_IFSOCK)
		return ('s');
	else
		return ('-');
}

static int	set_rights(char *tmp, t_lsarg *data)
{
	bzero(tmp, 42 * sizeof(char));
	tmp[0] = set_typeoffile(&(data->fstat));
	tmp[1] = (data->fstat.st_mode & S_IRUSR ? 'r' : '-');
	tmp[2] = (data->fstat.st_mode & S_IWUSR ? 'w' : '-');
	if (data->fstat.st_mode & S_ISUID)
		tmp[3] = (data->fstat.st_mode & S_IXUSR ? 'S' : 's');
	else
		tmp[3] = (data->fstat.st_mode & S_IXUSR ? 'x' : '-');
	tmp[4] = (data->fstat.st_mode & S_IRGRP ? 'r' : '-');
	tmp[5] = (data->fstat.st_mode & S_IWGRP ? 'w' : '-');
	if (data->fstat.st_mode & S_ISGID)
		tmp[6] = (data->fstat.st_mode & S_IXGRP ? 'S' : 's');
	else
		tmp[6] = (data->fstat.st_mode & S_IXGRP ? 'x' : '-');
	tmp[7] = (data->fstat.st_mode & S_IROTH ? 'r' : '-');
	tmp[8] = (data->fstat.st_mode & S_IWOTH ? 'w' : '-');
	if (data->fstat.st_mode & S_ISVTX)
		tmp[9] = (data->fstat.st_mode & S_IXOTH ? 't' : 'T');
	else
		tmp[9] = (data->fstat.st_mode & S_IXOTH ? 'x' : '-');
	tmp[100] = ' ';
	return (1);
}

int			ls_print_l(t_ls *ls, t_lsarg *d, t_list *lst)
{
	char		tmp[42];
	int			thogsmm[7];
	t_lsarg		*data;

	if (set_lns(lst, thogsmm) && lst && d->is_dir)
		ft_printf("total %d\n", thogsmm[0]);
	if (d->err)
		return (ls_print_helper(ls, d, 0));
	while (lst && (data = (t_lsarg *)(lst->content)) && set_rights(tmp, data))
	{
		ft_printf("%s %*d ", tmp, thogsmm[1], data->fstat.st_nlink);
		if (!(ls->opts & LS_G))
			ft_printf("%-*s  ", thogsmm[2],\
					getpwuid(data->fstat.st_uid)->pw_name);
		if (!(ls->opts & LS_O))
			ft_printf("%-*s  ", thogsmm[3], \
					getgrgid(data->fstat.st_gid)->gr_name);
		(ls->opts & LS_O) && (ls->opts & LS_G) ? write(1, "  ", 2) : 0;
		ls_print_size_min_maj(tmp[0], thogsmm + 4, &(data->fstat));
		print_date(tmp, data->fstat.st_mtime);
		ls_print_helper(ls, data, 0);
		ls_print_linked_file(data);
		lst = lst->next;
	}
	return (0);
}
