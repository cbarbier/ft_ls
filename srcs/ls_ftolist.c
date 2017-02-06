/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_ftolist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 18:31:14 by cbarbier          #+#    #+#             */
/*   Updated: 2017/02/06 20:38:20 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

static t_list	*read_to_list(DIR	*directory)
{
	t_dir	*ret;
	t_lsarg	data;
	t_list	lst;

	lst = 0;
	while ((ret = readdir(directory)))
	{
		bzero(&fstat, sizeof(t_stat));
		lstat(ret->d_name, &(data.fstat);
		ft_lstadd(&lst, &data, sizeof(sizeof(t_lsarg)));
	}
	return (lst);
}

t_list		*ls_ftolist(char	*filename)
{
	DIR		*directory;
	t_lsarg	data;

	bzero(&data, sizeof(t_lsarg));
	data.filename = filename;
	lstat(filename, &fstat);
	if (fstat.st_mode != S_IFDIR)
		return (ft_lstnew(&data, sizeof(t_lsarg)));
	if (!(directory = opendir(filename)))
	{
		data.err = errno;
		return (ft_lstnew(&data, sizeof(t_lsarg)));
	}
	return (read_to_list(directory));
}
