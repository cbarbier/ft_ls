/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 17:12:17 by cbarbier          #+#    #+#             */
/*   Updated: 2017/02/06 20:41:23 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static void	ls_core_recur_dir(t_list *dirs)
{
	t_list	*start;
	t_lsarg	*elm;

	start = dirs;
	while (dirs)
	{
		elm = (t_lsarg *)(dirs->content);
		ls_core(ls, elm->filename, ls_ftolist(elm->filename));
		dirs = dirs->next;
	}
	//ft_lstdel(start, );
}

int			ls_core(t_ls *ls, char	*filename, t_list *lst)
{	
	t_list	*dirs;
	t_lsarg	data;
	t_list	*start;

	ls_sort(ls, lst);
	start = lst;
	while (lst)
	{
		ft_bzero(&data, sizeof(t_lsarg));
		lstat(filename, &(data.fstat));
		if ((ls->opts & LS_RR) && data.fstat.st_mode == S_IFDIR)
			ft_lstpushback(&dirs, ft_lstnew(&data, sizeof(t_lsarg)));
		ls_print_file(ls, &data);
		lst = lst->next;
	}
	//ft_lstdel(start, );
	ls_core_recur_dir(dirs);
	return (1);
}
