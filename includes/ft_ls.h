/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorwin <jcorwin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 10:35:19 by sschmele          #+#    #+#             */
/*   Updated: 2019/05/19 06:21:28 by jcorwin          ###   ########.fr       */
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

# define FLAG_MIN 1
# define FLAG_L 2
# define FLAG_R 4
# define FLAG_RR 8
# define FLAG_A 16
# define FLAG_T 32
# define FLAG_GG 64
# define FLAG_P 128
# define FLAG_S 256
# define FLAG_U 512
# define FLAG_F 1024
# define FLAG_D 2048
# define FLAG_G 4096
# define FLAG_SS 8192
# define FLAG_C 16384
# define FLAG_N 32768

# define ST_NEW() stack_init()
# define ST_ADD(x, data) x->add(x, data)
# define ST_SORT(x, f) x->sort(x, f)
# define ST_DEL(x) x->del(x)
# define ST_ITER(x, f, param, rev) x->iter(x, f, param, rev)

typedef struct	s_plist
{
	char			*name;
	void			*data;
	size_t			num;
	struct s_plist	*next;
	struct s_plist	*prev;
}				t_plist;

typedef struct	s_stack
{
	t_plist		*list;
	size_t		counter;
	void		(*add)(struct s_stack *, void *data);
	void		(*iter)(struct s_stack *, void (*f)(void *, void *),
													void *param, int reverse);
	void		(*sort)(struct s_stack*, int (*f)(void *, void *));
	void		(*del)(struct s_stack *);
}				t_stack;

// typedef struct		s_file
// {
// 	struct stat		buf;
// 	char			*name;
// }					t_file;

void				*ft_xmalloc(size_t size);
void				free_data(struct s_file *file, void *name);
void				close_dirs(DIR *dir, void *null);

t_stack				*get_args(int *flags,  int argc, char **argv);
void				no_dir_or_file(char *dirname);

void				print_files(t_stack *files, int flags);
void				print_dir(char *path, int *flags);

t_stack				*stack_init();
void				*files_sort(int flags);
void				st_sort(t_stack *me, int (*f)(void *, void *));

#endif
