/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 15:05:09 by cbarbier          #+#    #+#             */
/*   Updated: 2017/02/14 10:54:58 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static int	ls_cmp_filename(t_list *a, t_list *b)
{
	char		*fa;
	char		*fb;

	fa = ((t_lsarg *)(a->content))->filename;
	fb = ((t_lsarg *)(b->content))->filename;
	return (ft_strcmp(fa, fb));
}

static int	ls_cmp_type_ascii(t_list *a, t_list *b)
{
	int		da;
	int		db;

	da = ((t_lsarg *)(a->content))->is_dir;
	db = ((t_lsarg *)(b->content))->is_dir;
	if (db == da)
		return (ls_cmp_filename(a, b));
	return (da - db);
}

static void	ft_lstfailput(t_list *l)
{
	int			i;
	t_lsarg		*ar;
	t_list		*elm;

	i = 0;
	while (l)
	{
		ar = (t_lsarg *)(l->content);
		ft_printf("ft_ls: %s: %s\n", ar->filename, strerror(ar->err));
		ft_strdel(&(ar->filename));
		ft_strdel(&(ar->fullpath));
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
	ft_lstsort(lst, ls_cmp_type_ascii);
	while (lst)
	{
		data = (t_lsarg *)(lst->content);
		ls_core(ls, data, ls_ftolist(ls, data->filename));
		ls->index++;
		lst = lst->next;
	}
}

int			main(int argc, char **argv)
{
	t_ls			ls;
	char			error;
	int				start;
	struct winsize	ws;

	ft_bzero(&ls, sizeof(t_ls));
	if ((start = ls_parse_options(&ls, argv, argc, &error)) < 0)
	{
		ft_printf("ft_ls: illegal option -- %c\n%s\n", error, USAGE);
		exit(1);
	}
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);
	ls.console_width = ws.ws_col;
	ls_arg_to_list(&ls, argv, start, argc);
	ls.count = argc - start;
	ft_lstsort(ls.fails, ls_cmp_filename);
	ft_lstfailput(ls.fails);
	ls_compute(&ls);
	ft_lstdel(&(ls.args), ls_del);
	return (0);
}
