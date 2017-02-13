/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print_c.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/13 15:18:39 by cbarbier          #+#    #+#             */
/*   Updated: 2017/02/13 21:35:13 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static t_list	*next_elem(t_list *lst, int ratio)
{
	while (lst && ratio--)
	{
		lst = lst->next;
	}
	return (lst);
}

static int		ls_dashc_helper(t_ls *ls, t_list *lst, int ratio, int max)
{
	int		rate;
	int		rows;
	int		stop;
	t_list	*tmp;

	if (!(rows = (int)((0.0 + ft_lstlen(lst)) / ratio)) + 0.5)
		rows = 1;
	ft_printf("nbrows : %d \nratio: %d\n", rows, ratio);
	stop = rows;
	while (lst && stop--)
	{
		tmp = lst;
		rate = ratio;
		while (tmp || rate--)
		{
			if (tmp)
				ls_print_helper(ls, (t_lsarg *)(tmp->content), max);
			ft_printf("%*c", (tmp ? 1 : max + 1) , ' ');
			tmp = next_elem(tmp, rows);
		}
		lst = lst->next;
		write(1, "\n", 1);
	}
	return (1);
}

int				ls_print_c(t_ls *ls, t_list *lst)
{
	struct winsize	ws;
	t_list			*tmp;
	int				max;
	int				val;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);
	tmp = lst;
	max = 0;
	while (tmp)
	{
		if ((val = ft_strlen(((t_lsarg *)tmp->content)->filename)) > max)
			max = val;
		tmp = tmp->next;
	}
	ft_printf("{grn}terminal width is: %d max :%d{no}\n", ws.ws_col, max);
	val = ws.ws_col / (ls->opts & LS_FF ? (max + 2) : (max + 1));
	ls_dashc_helper(ls, lst, val, max);
	return (1);
}
