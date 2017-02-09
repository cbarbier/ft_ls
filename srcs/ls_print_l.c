/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print_l.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 10:06:07 by cbarbier          #+#    #+#             */
/*   Updated: 2017/02/09 17:25:47 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

static void	print_date(char *tmp, time_t	fdate)
{
	time_t	curtime;
	char	*snow;
	char	*sfil;

	time(&curtime);
	snow = ctime(&curtime);
	sfil = ctime(&fdate);
	bzero(tmp, 13 * sizeof(char));
	ft_strncat(tmp, sfil + 4, 3);
	ft_strcat(tmp, (ft_isdigit(sfil[10]) ? " " : "  "));
	ft_strncat(tmp, sfil + 9, ft_isdigit(sfil[10]) ? 2 : 1);
	ft_strcat(tmp, " ");
	if (!(curtime - fdate > 15778458 || fdate - curtime > 3600))
		ft_strncat(tmp, sfil + 11, 5);
	else
		ft_strncat(ft_strcat(tmp, " "), sfil + 21, 4);
	ft_printf("%s ", tmp);
}

static void	set_lns(t_list *lst, int *thogs)
{
	int 	res;
	t_stat	*st;

	bzero(thogs, 5 * sizeof(int));
	while (lst)
	{
		st = &(((t_lsarg *)(lst->content))->fstat);
		thogs[0] += st->st_blocks;
		if ((res = ft_nblen(st->st_nlink)) > thogs[1])
			thogs[1] = res;
		if ((res = ft_strlen(getpwuid(st->st_uid)->pw_name)) > thogs[2])
			thogs[2] = res;
		if ((res = ft_strlen(getgrgid(st->st_gid)->gr_name)) > thogs[3])
			thogs[3] = res;
		if ((res = ft_nblen(st->st_size)) > thogs[4])
			thogs[4] = res;
		lst = lst->next;
	}
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

static void	set_rights(char *tmp, t_lsarg *data)
{
	bzero(tmp, 13 * sizeof(char));
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
	tmp[10] = ' ';
}

int			ls_print_l(t_list *lst)
{
	char		tmp[13];
	int			thogs[5];
	t_lsarg		*data;

	set_lns(lst, thogs);
	if (lst && ((t_lsarg *)(lst->content))->fstat.st_mode & S_IFDIR)
		ft_printf("total %d\n", thogs[0]);
	while (lst)
	{
		data = (t_lsarg *)(lst->content);
		set_rights(tmp, data);
		ft_printf("%s ", tmp);
		ft_printf("%*d ", thogs[1], data->fstat.st_nlink);
		ft_printf("%*s  ", thogs[2], getpwuid(data->fstat.st_uid)->pw_name);
		ft_printf("%*s  ", thogs[3], getgrgid(data->fstat.st_gid)->gr_name);
		ft_printf("%*d ", thogs[4], data->fstat.st_size);
		print_date(tmp, data->fstat.st_mtime);
		ft_printf("%s", data->filename);
		ls_print_linked_file(data);
		lst = lst->next;
	}
	return (0);
}
