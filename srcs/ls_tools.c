/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 17:46:13 by cbarbier          #+#    #+#             */
/*   Updated: 2017/02/17 13:28:33 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void		ls_del(void *e, size_t s)
{
	t_lsarg		*d;

	d = (t_lsarg *)e;
	ft_strdel(&(d->filename));
	ft_strdel(&(d->fullpath));
	bzero(e, s);
	free(e);
}

char		*mkpth(char *a, char *b)
{
	int			len;
	char		*res;
	int			home;

	len = ft_strlen(a);
	home = a[len - 1] != '/' ? 1 : 0;
	len += ft_strlen(b) + home;
	if (!(res = ft_strnew(len)))
		return (0);
	ft_strcat(res, a);
	if (home)
		ft_strcat(res, "/");
	ft_strcat(res, b);
	return (res);
}

void		ls_print_linked_file(t_lsarg *d)
{
	char	buf[100];

	bzero(buf, 100 * sizeof(char));
	if ((d->fstat.st_mode & S_IFMT) == S_IFLNK)
		readlink(d->fullpath, buf, 100 * sizeof(char));
	ft_printf("%s%s\n", (*buf ? " -> " : ""), buf);
}

int			ls_print_size_min_maj(char t, int *smm, t_stat *st)
{
	if (t != 'c' && t != 'b')
		return (ft_printf("%*d ", smm[0], st->st_size));
	ft_printf("%*d, ", smm[1], ((st->st_rdev >> 24) & 0xff));
	ft_printf("%*d ", smm[2], st->st_rdev & 0xffffff);
	return (0);
}

void		ls_set_lns_min_maj(int *thogsmm, t_stat *st)
{
	int		res;

	if ((st->st_mode & S_IFMT) != S_IFCHR
			&& (st->st_mode & S_IFMT) != S_IFBLK)
		return ;
	if ((res = ft_nblen((st->st_rdev >> 24) & 0xff)) > thogsmm[5])
		thogsmm[5] = res;
	if ((res = ft_nblen(st->st_rdev & 0xffffff)) > thogsmm[6])
		thogsmm[6] = res;
}
