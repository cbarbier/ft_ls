/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 15:05:09 by cbarbier          #+#    #+#             */
/*   Updated: 2017/02/07 09:35:56 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/ft_ls.h"
#include <sys/ioctl.h>

static int		ft_cmp(t_list *a, t_list *b)
{
	char *fa;
	char *fb;

	fa = (char *)(a->content);
	fb = (char *)(b->content);
	return (ft_strcmp(fa, fb));
}

static void		ft_lstreverse(t_list **alst)
{
	t_list	*lst;
	t_list	*tmp;
	t_list	*tmp2;

	if (!alst)
		return ;
	lst = *alst;
	tmp = 0;
	while (lst)
	{
		tmp2 = lst->next;
		lst->next = tmp;
		tmp = lst;
		lst = tmp2;
	}
	if (tmp)
		*alst = tmp;
}

int		main(int argc, char **argv)
{
	DIR		*directory;
	t_dir	*ret;
	t_stat	fstat;
	t_list	*lst;
	int		index;
	struct winsize size;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
	ft_printf("{grn}the number of col in this terminal is : {yel}%d{no}\n***\n", size.ws_col);
	if (argc == 1)
		return (0);
	if (!(directory = opendir(argv[1])))
		perror("test");
	else
	{
		stat(argv[1], &fstat);
		ft_printf("its a directory total : %llu\n", fstat.st_blocks);
	}
	while (directory && (ret = readdir(directory)))
	{
		lstat(ret->d_name, &fstat);
		ft_printf("inode: %d %s %d\n", ret->d_ino, ret->d_name, ret->d_type);
		ft_printf("size: %d rights: %b  nblink: %d nblocks: %d\n", fstat.st_size, fstat.st_mode, fstat.st_nlink, fstat.st_blocks);
	}
	index = 0;
	lst = NULL;
	while (index < argc)
	{
		ft_lstpushback(&lst, ft_lstnew(argv[index], ft_strlen(argv[index]) + 1));
		index++;
	}
	ft_lstsort(lst, &ft_cmp);
	index = 0;
	ft_printf("\n{blu}***\nlist @ %#X\n***{no}\n", lst);
	ft_printf("test of ft_lstreverse\n");
	ft_lstreverse(&lst);
	while (lst)
	{
		ft_printf("elem %05d content: %s\n", index++, (char *)(lst->content));
		lst = lst->next;
	}
	return (0);
}
