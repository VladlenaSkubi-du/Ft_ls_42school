/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorwin <jcorwin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 10:35:19 by sschmele          #+#    #+#             */
/*   Updated: 2019/05/13 19:13:21 by jcorwin          ###   ########.fr       */
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
# include "libft.h"
# include "ft_printf.h"

# define FLAG_ONE 1
# define FLAG_L 2
# define FLAG_R 4
# define FLAG_RR 8
# define FLAG_A 16
# define FLAG_T 32
# define FLAG_G 64
# define FLAG_P 128
# define FLAG_S 256

typedef struct		s_file
{
	struct stat		buf;
	char			*name;
	struct s_file	*prev;
	struct s_file	*next;
	int				fromstart;
	// int				tostart;
}					t_file;

typedef struct		s_param
{
	t_file			*file;
	int				flags;
}					t_param;

void				*ft_xmalloc(size_t size);

t_file				*file_new(t_file *start);
t_file				*file_cut(t_file *start, t_file *node);
void				file_insert(t_file *prev, t_file *node);
t_file				*file_swap(t_file *start, t_file *left, t_file *right);
t_file				*file_del(t_file *start);
void				file_count(t_file *start);
void				file_foreach(t_file *start, void (*f)(t_file *cur));

int					file_strcmp(t_file *left, t_file *right);
void				quickSort(t_file *start, t_file *left, t_file *right,
									int (*f)(t_file *left, t_file *right));

#endif
