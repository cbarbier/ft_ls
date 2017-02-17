/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_tools2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 14:27:06 by cbarbier          #+#    #+#             */
/*   Updated: 2017/02/17 15:19:25 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

char		*ls_get_filename(char *filename)
{
	char		*tmp;

	if ((tmp = ft_strrchr(filename, '/')) && *(++tmp))
		return (ft_strdup(tmp));
	return (ft_strdup(filename));
}

int			ls_stat(t_ls *ls, char *f, t_stat *st)
{
	lstat(f, st);
	if (!(((ls->opts & LS_L)
		&& (st->st_mode & S_IFMT) == S_IFLNK)))
		stat(f, st);
	return (1);
}

int			ls_set_acl(char *c, t_lsarg *d)
{
	acl_t		acl;

	if (listxattr(d->fullpath, NULL, 0, XATTR_NOFOLLOW) > 0)
		*c = '@';
	else if ((acl = acl_get_file(d->fullpath, ACL_TYPE_EXTENDED)))
	{
		acl_free(acl);
		*c = '+';
	}
	else
		*c = ' ';
	return (1);
}
