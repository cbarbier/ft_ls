/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 15:05:09 by cbarbier          #+#    #+#             */
/*   Updated: 2017/02/01 15:30:41 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

int		main(int argc, char **argv)
{
	if (argc && argv[0])
		ft_printf("{grn}welcome to project ft_ls{no}\n");
	return (0);
}
