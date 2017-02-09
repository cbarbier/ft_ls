/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 15:25:59 by cbarbier          #+#    #+#             */
/*   Updated: 2017/02/09 17:55:42 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
# include "../libft/includes/libft.h"
# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <pwd.h>
# include <grp.h>
# include <uuid/uuid.h>
# include <time.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# define USAGE		"usage: ft_ls [-lraRtLC1] [file ...]"
# define OPTIONS	"lratRLC1"
# define LS_L		1 
# define LS_R		2 
# define LS_A		4 
# define LS_RR		8 
# define LS_T		16
# define LS_LL		32
# define LS_C		64
# define LS_1		128

typedef struct dirent		t_dir;
typedef struct stat			t_stat;
typedef struct 				s_lsarg
{
	char			*filename;
	char			*fullpath;
	char			err;
	t_stat			fstat;
}							t_lsarg;
typedef struct				s_ls
{
	short int		opts;
	t_list			*args;
	short int		count;
	t_list			*fails;
}							t_ls;

int				ls_parse_options(t_ls *ls, char **argv, int argc, char *e);
int				ls_arg_to_list(t_ls *ls, char **argv,  int start, int end);
int				ls_core(t_ls *ls, t_lsarg *data, t_list *lst);
t_list			*ls_ftolist(t_ls *ls, char	*filename);
void			ls_sort(t_ls * ls, t_list	**alist);
int				ls_print_file(t_ls *ls, t_lsarg *d, t_list *lst);
int				ls_print_l(t_list *lst);
char			*mkpth(char *a, char *b);

#endif
