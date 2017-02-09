/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 17:46:13 by cbarbier          #+#    #+#             */
/*   Updated: 2017/02/07 18:19:00 by cbarbier         ###   ########.fr       */
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
