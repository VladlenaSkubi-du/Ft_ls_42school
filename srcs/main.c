/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorwin <jcorwin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 10:50:06 by sschmele          #+#    #+#             */
/*   Updated: 2019/05/19 05:51:36 by jcorwin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <dirent.h>

#include "ft_ls.h"

void			close_dirs(DIR *dir, void *null)
{
	if (!null)
		closedir(dir);
}

void			free_data(struct s_file *file, void *name)
{
	if (file)
	{
		if (name)
			free(file->name);
		free(file);
	}
}

static void		check_arg(char *str, t_stack *params)
{
	DIR			*dir;
	t_file		*file;
	t_stack		*files;
	t_stack		*dirs;

	files = params->list->data;
	dirs = params->list->next->data;
	file = (t_file *)ft_xmalloc(sizeof(t_file));
	if (stat(str, &file->buf))
	{
		no_dir_or_file(str);
		free(file);
		return ;
	}
	file->name = ft_strdup(str);
	if (file->buf.st_mode & S_IFDIR)
	{
		ST_ADD(dirs, file->name);
		free(file);
	}
	else
		ST_ADD(files, file);
}

static void		throw_args(t_stack *args, t_stack *params, int flags)
{
	t_stack		*files;
	t_stack		*dirs;

	files = params->list->data;
	dirs = params->list->next->data;
	params->counter = flags;
	ST_ITER(args, (void (*)(void *, void *))check_arg, params, flags & FLAG_R);
	print_files(files, flags);
	ST_ITER(dirs, (void (*)(void *, void *))print_dir, &flags, flags & FLAG_R);
	ST_DEL(args);
	ST_ITER(files, (void (*)(void *, void *))free_data, (void *)1, 0);
	ST_DEL(files);
	ST_ITER(dirs, (void (*)(void *, void *))free_data, NULL, 0);
	ST_DEL(dirs);
}

int				main(int argc, char **argv)
{
	int			flags;
	t_stack		*args;
	t_file		file;
	t_stack		*params;

	params = ST_NEW();
	ST_ADD(params, ST_NEW());
	ST_ADD(params, ST_NEW());
	flags = 0;
	params->counter = flags;
	if ((args = get_args(&flags, argc, argv)))
		throw_args(args, params, flags);
	else
		print_dir(".", &flags);
	ST_DEL(params);
	return (0);
}
