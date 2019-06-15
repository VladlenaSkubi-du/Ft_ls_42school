/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorwin <jcorwin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 10:50:06 by sschmele          #+#    #+#             */
/*   Updated: 2019/06/12 17:43:46 by jcorwin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			del_file(t_file *file, void *null)
{
	if (file && !null)
	{
		if (file->path)
			free(file->path);
		if (file->name)
			free(file->name);
		if (file->dir)
			closedir(file->dir);
		free(file);
	}
}

static void		fill_type(t_file *file)
{
	if (S_ISDIR(file->info.st_mode))
		file->type = 'd';
	else if (S_ISBLK(file->info.st_mode))
		file->type = 'b';
	else if (S_ISCHR(file->info.st_mode))
		file->type = 'c';
	else if (S_ISFIFO(file->info.st_mode))
		file->type = 'p';
	else if (S_ISLNK(file->info.st_mode))
		file->type = 'l';
	else if (S_ISREG(file->info.st_mode))
		file->type = '-';
}

static void		check_arg(t_file *file, t_stack *params)
{
	t_stack		*dirs;
	t_stack		*files;

	files = params->data[0];
	dirs = params->data[1];
	if (!lstat(file->name, &file->info))
	{
		if (file->info.st_mode & S_IFDIR && ~params->size & FLAG_D)
			ST_ADD(dirs, file);
		else
			ST_ADD(files, file);
		if (params->size & FLAG_L)
		{
			fill_type(file);
			if (file->type == 'b' || file->type == 'c')
				params->size |= FLAG_DEVICE;
		}
	}
	else
		print_err(file->name);
}

static void		throw_args(t_stack *args, t_stack *params, int flags)
{
	t_stack		*files;
	t_stack		*dirs;

	files = params->data[0];
	dirs = params->data[1];
	params->size = flags;
	ST_ITER(args, (void (*)(void *, void *))check_arg, params, flags & FLAG_R);
	flags = params->size;
	if (dirs->data && dirs->data[0] && dirs->data[1])
		flags |= FLAG_FOLDER_RR;
	fill_and_print_stackfiles(files, &flags, 0);
	ST_ITER(dirs, (void (*)(void *, void *))print_dir, &flags,
														flags & FLAG_R);
	ST_ITER(args, (void (*)(void *, void *))del_file, NULL, 0);
	ST_DEL(files);
	ST_DEL(dirs);
	ST_DEL(args);
}

int				main(int argc, char **argv)
{
	int			flags;
	t_stack		*args;
	t_file		*file;
	t_stack		*params;

	params = ST_NEW();
	ST_ADD(params, ST_NEW());
	ST_ADD(params, ST_NEW());
	flags = isatty(1) ? (FLAG_C | FLAG_ATTY) : FLAG_ONE;
	if (!(args = get_args(&flags, argc, argv)))
	{
		args = ST_NEW();
		file = (t_file *)ft_xmalloc(sizeof(t_file));
		file->name = ft_strdup(".");
		file->path = ft_strdup(file->name);
		ST_ADD(args, file);
	}
	throw_args(args, params, flags);
	ST_DEL(params);
	buf_add(NULL, 0);
	return (0);
}
