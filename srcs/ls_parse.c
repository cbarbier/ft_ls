/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 11:45:43 by cbarbier          #+#    #+#             */
/*   Updated: 2017/02/06 14:28:46 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

static void		ls_set_options(t_ls *ls, char opt)
{
	if (opt == 'l')
		ls->opts += LS_L;
	else if (opt == 'r')
		ls->opts += LS_R;
	else if (opt == 'a')
		ls->opts += LS_A;
	else if (opt == 't')
		ls->opts += LS_T;
	else if (opt == 'R')
		ls->opts += LS_RR;
	else if (opt == 'u')
		ls->opts += LS_U - (ls->opts & LS_T ? LS_T : 0); 
	else if (opt == 'L')
		ls->opts += LS_LL;
	else if (opt == 'C')
		ls->opts += LS_C - (ls->opts & LS_1 ? LS_1 : 0); 
	else if (opt == '1')
		ls->opts += LS_1 - (ls->opts & LS_C ? LS_C : 0);
}

int				ls_parse_options(t_ls *ls, char **argv, int argc, char *error)
{
	int		index;
	int		stop;
	char	*tmp;

	stop = 1;
	index = 1;
	while (index < argc && (stop = ft_strcmp(argv[index], "--"))
			&& argv[index][0] == '-' && argv[index][1])
	{
		printf("%s\n", argv[index]);
		tmp = argv[index] + 1;
		while (*tmp && ft_strchr(OPTIONS, *tmp))
				ls_set_options(ls, *(tmp++));
		if (*tmp && (*error = *tmp))
			return (-1);
		index++;
	}
	return (!stop ? ++index : index);
}
