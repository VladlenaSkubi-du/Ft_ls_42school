/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 10:35:19 by sschmele          #+#    #+#             */
/*   Updated: 2019/06/18 18:56:39 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <unistd.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <pwd.h>
# include <uuid/uuid.h>
# include <grp.h>
# include <sys/xattr.h>
# include <time.h>
# include <stdlib.h>
# include <stdio.h>
# include <termios.h>
# include <errno.h>
# include "libft.h"
# include "ft_printf.h"

# include <sys/acl.h> //для acl
# include <sys/ioctl.h> //для ширины терминала
# include <dirent.h>

# define OUT_BUF (size_t)100000

# define FLAG_ONE 0x1
# define FLAG_L 0x2
# define FLAG_R 0x4
# define FLAG_RR 0x8
# define FLAG_A 0x10
# define FLAG_T 0x20
# define FLAG_GG 0x40
# define FLAG_P 0x80
# define FLAG_S 0x100
# define FLAG_U 0x200
# define FLAG_F 0x400
# define FLAG_D 0x800
# define FLAG_G 0x1000
# define FLAG_SS 0x2000
# define FLAG_CC 0x4000
# define FLAG_FOLDER_RR 0x8000
# define FLAG_C 0x10000
# define FLAG_FF 0x20000
# define FLAG_MINUS 0x40000
# define FLAG_ATTY 0x80000

# define ST_NEW() stack_init()
# define ST_ADD(x, data) x->add(x, data)
# define ST_SORT(x, f) x->sort(x, f)
# define ST_DEL(x) x = x->del(x)
# define ST_ITER(x, f, param, rev) x->iter(x, f, param, rev)

typedef struct	s_stack
{
	void				**data;
	size_t				size;
	size_t				next_up;
	void				(*add)(struct s_stack *, void *data);
	void				(*iter)(struct s_stack *, void (*f)(void *, void *),
													void *param, int reverse);
	void				(*sort)(struct s_stack*, int (*f)(void *, void *));
	struct	s_stack		*(*del)(struct s_stack *);
}				t_stack;

typedef struct		s_file
{
	char			*path;
	struct stat		info;
	char			type;
	char			*total;
	char			*mode;
	char			*link;
	struct passwd	*uid;
	struct group	*gid;
	char			*size;
	char			*time;
	char			color[9];
	char			*name;
	DIR				*dir;
}					t_file;

t_stack				*stack_init();
t_stack				*get_args(int *flags,  int argc, char **argv);
void				fill_type(t_file *file);
void				st_sort(t_stack *me, int (*f)(void *, void *));
void				print_dir(t_file *file, int *flags);
void				print_err(char *dirname);
void  				usage(void);
void				ft_printerr(char *str, size_t size);
void				*files_sort(int flags);
int					file_strcmp(t_file *left, t_file *right);
void				fill_and_print_stackfiles(t_stack *files, int *flags, int total);
void				fill_mode(t_file *file);
void				fill_time(t_file *file, int *columns);
void				fill_link(t_file *file);
void				fill_minmaz(t_file *file);
void				change_name(t_file *file, int flags);
void				separate_output(int flags, int *columns);
void				print_stackfile(t_file *file, int *col);
int					get_terminal_width(void);
void				buf_add(char *str, size_t size);
void				buf_add_num(unsigned int n);
void				buf_fill(char *str, size_t len, size_t size, int left);
void				buf_err(char *str);
void				del_file(t_file *file, void *null);
void				*ft_xmalloc(size_t size);
void				ft_stradd_nb(char *s, long nb);
char        		*ft_strs_rejoin(char *main, char **arr, int size);
#endif
