/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 15:05:09 by cbarbier          #+#    #+#             */
/*   Updated: 2017/02/07 20:32:15 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

static int	ls_cmp_filename(t_list *a, t_list *b)
{
	char *fa;
	char *fb;

	fa = ((t_lsarg *)(a->content))->filename;
	fb = ((t_lsarg *)(b->content))->filename;
	return (ft_strcmp(fa, fb));
}

static void	ft_lstfailput(t_list *l)
{
	int i;
	t_lsarg	*ar;
	t_list	*elm;

	i = 0;
	while (l)
	{
		ar = (t_lsarg *)(l->content);
		printf("ft_ls: %s: %s\n", ar->filename, strerror(ar->err));
		ft_strdel(&(ar->filename));
		elm = l->next;
		free(l->content);
		free(l);
		l = elm;
	}
}

static void	ls_compute(t_ls *ls)
{
	t_list		*lst;
	t_lsarg		*data;

	lst = ls->args;
	while (lst)
	{
		data = (t_lsarg *)(lst->content);
		ls_core(ls, data->filename, ls_ftolist(ls, data->filename));
		lst = lst->next;
	}
}

int			main(int argc, char **argv)
{
	t_ls		ls;
	char		error;
	int			start;

	ft_bzero(&ls, sizeof(t_ls));
	if ((start = ls_parse_options(&ls, argv, argc, &error)) < 0)
	{
		printf("ft_ls: illegal option -- %c\n%s\n", error, USAGE);
		return (0);
	}
	if (start == argc)
		return (ls_core(&ls, ".", ls_ftolist(&ls, ".")));
	ls.count = argc - start - 1; 
	ls_arg_to_list(&ls, argv, start, argc);
	ft_lstsort(ls.fails, ls_cmp_filename);
	ft_lstfailput(ls.fails);
	ls_compute(&ls);
	return (0);
}