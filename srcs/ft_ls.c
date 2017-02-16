/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 15:05:09 by cbarbier          #+#    #+#             */
/*   Updated: 2017/02/16 17:39:32 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

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
	if (ls->files)
	{
		data = (t_lsarg *)ft_memalloc(sizeof(t_lsarg));
		ls_core(ls, data, ls->files);
		free(data);
	}
	while (lst)
	{
		data = (t_lsarg *)(lst->content);
		ls_core(ls, data, ls_ftolist(ls, data));
		ls->index++;
		lst = lst->next;
	}
}

static int	ls_exit_on_emptyarg(char **ag, int start, int end)
{
	while (start < end)
	{
		if (!ft_strcmp(ag[start], ""))
		{
			ft_putstr("ft_ls: fts_open: No such file or directory\n");
			exit(1);
		}
		start++;
	}
	return (1);
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
	ls_exit_on_emptyarg(argv, start, argc);
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
