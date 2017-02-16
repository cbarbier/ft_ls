/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 15:25:59 by cbarbier          #+#    #+#             */
/*   Updated: 2017/02/16 08:15:53 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
# include "../libft/includes/libft.h"
# include <dirent.h>
# include <sys/stat.h>
# include <sys/xattr.h>
# include <sys/acl.h>
# include <sys/types.h>
# include <pwd.h>
# include <grp.h>
# include <uuid/uuid.h>
# include <time.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <sys/ioctl.h>
# define USAGE		"usage: ft_ls [-lraRtC1goGFS] [file ...]"
# define OPTIONS	"lratRC1goGFS"
# define LS_L		1
# define LS_R		2
# define LS_A		4
# define LS_RR		8
# define LS_T		16
# define LS_CC		32
# define LS_1		64
# define LS_G		128
# define LS_O		256
# define LS_GG		512
# define LS_FF		1024
# define LS_SS		2048

typedef struct dirent	t_dir;
typedef struct stat		t_stat;
typedef struct			s_lsarg
{
	char			*filename;
	char			*fullpath;
	char			err;
	char			is_dir;
	t_stat			fstat;
}						t_lsarg;
typedef struct			s_ls
{
	short int		opts;
	t_list			*args;
	short int		count;
	int				index;
	int				console_width;
	t_list			*fails;
}						t_ls;

int						ls_parse_options\
							(t_ls *ls, char **argv, int argc, char *e);
int						ls_arg_to_list\
							(t_ls *ls, char **argv, int start, int end);
int						ls_core(t_ls *ls, t_lsarg *data, t_list *lst);
t_list					*ls_ftolist(t_ls *ls, char	*filename);
void					ls_sort(t_ls *ls, t_list **alist);
int						ls_print(t_ls *ls, t_lsarg *d, t_list *lst, int depth);
int						ls_print_l(t_ls *ls, t_lsarg *data, t_list *lst);
char					*mkpth(char *a, char *b);
void					ls_print_linked_file(t_lsarg *d);
int						ls_print_size_min_maj(char t, int *mm, t_stat *st);
void					ls_set_lns_min_maj(int *thogsmm, t_stat *st);
void					ls_del(void	*e, size_t s);
int						ls_print_c(t_ls *ls, t_list *lst);
int						ls_print_helper(t_ls *ls, t_lsarg *d, int w);
int						ls_set_acl(char *c, t_lsarg *d);
int						ls_cmp_filename(t_list *a, t_list *b);
int						ls_stat(t_ls *ls, char *f, t_stat *st);

#endif
