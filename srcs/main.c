/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 10:50:06 by sschmele          #+#    #+#             */
/*   Updated: 2019/08/28 18:08:51 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			del_file(t_file *file, void *null)
{
	null = 0;
	free(file->uid);
	free(file->gid);
	free(file->path);
	free(file->total);
	free(file->mode);
	free(file->link);
	free(file->size);
	free(file->time);
	free(file->name);
	if (file->dir)
		closedir(file->dir);
	free(file);
}

static void		check_arg(t_file *file, t_stack *params)
{
	t_stack		*dirs;
	t_stack		*files;
	int			tmp;

	files = params->data[0];
	dirs = params->data[1];
	if (params->size & (FLAG_G | FLAG_L))
		tmp = lstat(file->name, &file->info);
	else
		tmp = stat(file->name, &file->info);
	if (!tmp)
	{
		if (file->info.st_mode & S_IFDIR && ~params->size & FLAG_D)
			dirs->add(dirs, file);
		else
			files->add(files, file);
		if (params->size & (FLAG_L | FLAG_GG | FLAG_FF | FLAG_G))
			fill_type(file);
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
	args->iter(args, (void (*)(void *, void *))check_arg, params, 0);
	if (dirs->data && dirs->data[0] && dirs->data[1])
		flags |= FLAG_FOLDER_RR;
	if (files->data[0])
		fill_and_print_stackfiles(files, &flags, 0);
	dirs->iter(dirs, (void (*)(void *, void *))print_dir, &flags,
														flags & FLAG_R);
	args->iter(args, (void (*)(void *, void *))del_file, NULL, 0);
	files->del(files);
	dirs->del(dirs);
	args->del(args);
}

int				main(int argc, char **argv)
{
	int			flags;
	t_stack		*args;
	t_file		*file;
	t_stack		*params;

	params = stack_init();
	params->add(params, stack_init());
	params->add(params, stack_init());
	flags = isatty(1) ? (FLAG_CC | FLAG_ATTY) : FLAG_ONE;
	if (!(args = get_args(&flags, argc, argv)))
	{
		args = stack_init();
		file = (t_file *)ft_xmalloc(sizeof(t_file));
		file->name = ft_strdup(".");
		file->path = ft_strdup(file->name);
		args->add(args, file);
	}
	throw_args(args, params, flags);
	params->del(params);
	buf_add(NULL, 0);
	if (errno)
		return (1);
	return (0);
}
