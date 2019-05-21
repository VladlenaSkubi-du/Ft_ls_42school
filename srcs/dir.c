/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorwin <jcorwin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 16:50:56 by jcorwin           #+#    #+#             */
/*   Updated: 2019/05/20 20:26:07 by jcorwin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		print_inner(t_file *file, int *flags)
{
	*flags |= FLAG_N;
	if (ft_strcmp(file->name, ".") && ft_strcmp(file->name, ".."))
	{
		ft_putchar('\n');
		print_dir(file, flags);
	}
}

// static void		get_files(t_stack *files, char *path, DIR *dir, int flags)
// {
// 	t_file				*file;
// 	struct dirent		*entry;


// }

void			print_dir(t_file *file, int *flags)
{
	t_stack				*dirs;
	t_stack				*files;
	struct dirent		*entry;
	char				*tmp;
	t_file				*inner_file;

	if (*flags & FLAG_N)
	{
		ft_putstr(file->name);
		ft_putstr(":\n");
	}
	if (!(file->dir = opendir(file->name)))
	{
		print_err(file->name);
		return ;
	}
	files = ST_NEW();
	dirs = ST_NEW();
	// get_files(files, path, dir, *flags);
	while ((entry = readdir(file->dir)))
	{
		if (*entry->d_name == '.')
			continue ;
		inner_file = (t_file *)ft_xmalloc(sizeof(t_file));
		inner_file->name = ft_strrejoin(ft_strjoin(file->name, "/"), entry->d_name);
		if (!stat(inner_file->name, &inner_file->info))
		{
			ST_ADD(files, inner_file);
			if (inner_file->info.st_mode & S_IFDIR)
				ST_ADD(dirs, inner_file);
		}
		else
		{
			print_err(inner_file->name);
			free(inner_file->name);
			inner_file->name = NULL;
			free(inner_file);
		}
	}
	ST_SORT(files, files_sort(*flags));
	ST_SORT(dirs, files_sort(*flags));
	print_files(files, *flags);
	if (*flags & FLAG_RR)
		ST_ITER(dirs, (void (*)(void *, void *))print_inner, flags, 0);
	ST_ITER(files, (void (*)(void *, void *))del_files, NULL, *flags & FLAG_R);
	ST_DEL(dirs);
	ST_DEL(files);
}
