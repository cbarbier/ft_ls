/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 17:46:13 by cbarbier          #+#    #+#             */
/*   Updated: 2017/02/10 16:07:52 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

char		*mkpth(char *a, char *b)
{
	int		len;
	char	*res;

	len = ft_strlen(a) + ft_strlen(b) + 2;
	if (!(res = (char *)ft_memalloc((len + 1) * sizeof(char))))
		return (0);
	ft_strcat(res, a);
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

int			ls_print_size_min_maj(char t, int *smM, t_stat *st)
{
	if (t != 'c' && t != 'b')
		return (ft_printf("%*d ", smM[0], st->st_size));
	ft_printf("%*d, ", smM[1], ((st->st_rdev >> 24) & 0xff));
	ft_printf("%*d ", smM[2], st->st_rdev & 0xffffff);
	return (0);
}

void		ls_set_lns_min_maj(int *thogsmM, t_stat *st)
{
	int		res;

	if ((st->st_mode & S_IFMT) != S_IFCHR
			&& (st->st_mode & S_IFMT) != S_IFBLK)
		return ;
	if ((res = ft_nblen((st->st_rdev >> 24) & 0xff)) > thogsmM[5])
		thogsmM[5] = res;
	if ((res = ft_nblen(st->st_rdev & 0xffffff)) > thogsmM[6])
		thogsmM[6] = res;
}
