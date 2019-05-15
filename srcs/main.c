/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorwin <jcorwin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 10:50:06 by sschmele          #+#    #+#             */
/*   Updated: 2019/05/15 16:18:30 by jcorwin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <dirent.h>

#include "ft_ls.h"

static void		print_inner(t_file *file, int *flags);

static void		free_data(void *ptr, void *null)
{
	if (!null)
	{
		free(ptr);
	}
}

static void		print_dir(DIR *dir, int *flags)
{
	t_file				*file;
	static t_stack		*files = NULL;
	struct dirent		*entry;

	files = stack_init();
	while ((entry = readdir(dir)))
	{
		if (!(*flags & (FLAG_F | FLAG_A)) && *entry->d_name == '.')
			continue ;
		file = (t_file *)ft_xmalloc(sizeof(t_file));
		file->name = entry->d_name;
		stat(file->name, &(file->buf));
		files->add(files, file);
	}
	files->sort(files, files_sort(*flags));
	print_files(files, *flags);
	if (*flags & FLAG_RR)
		files->iter(files, (void (*)(void *, void *))print_inner, flags);
	files->del(files);
	closedir(dir);
}

static void		print_inner(t_file *file, int *flags)
{
	DIR		*dir;

	if (ft_strcmp(file->name, "..") && ft_strcmp(file->name, ".") && file->buf.st_mode & S_IFDIR)
	{
		dir = opendir(file->name);
		ft_putstr(file->name);
		ft_putstr(":\n");
			print_dir(dir, flags);
		ft_putendl("");
	}
}

static void		check_arg(char *str, t_stack *param)
{
	DIR			*dir;
	t_file		*file;
	t_stack		*files;
	t_stack		*dirs;

	files = param->list->data;
	dirs = param->list->next->data;
	dir = opendir(str);
	if (!dir || param->counter & FLAG_D)
	{
		if (errno == ENOENT)
			no_dir_or_file(str);
		if (errno == ENOTDIR)
		{
			file = (t_file *)ft_xmalloc(sizeof(t_file));
			file->name = str;
			stat(str, &file->buf);
			files->add(files, file);
		}
	}
	else
		dirs->add(dirs, dir);
}

int				main(int argc, char **argv)
{
	int			flags;
	t_stack		*args;
	t_stack		*files;
	t_stack		*dirs;
	t_stack		*param;

	flags = 0;
	param = stack_init();
	files = stack_init();
	dirs = stack_init();
	param->add(param, files);
	param->add(param, dirs);
	if ((args = get_args(&flags, argc, argv)))
	{
		param->counter = flags;
		args->iter(args, (void (*)(void *, void *))check_arg, param);
		args->del(args);
		// flags & FLAG_R ? args->iterr(args, (void (*)(void *, void *))check_arg, param) :
		// 					args->iter(args, (void (*)(void *, void *))check_arg, param);
	}
	else
		dirs->add(dirs, opendir("."));
	print_files(files, flags);
	dirs->iter(dirs, (void (*)(void *, void *))print_dir, &flags);
	return (0);
}
