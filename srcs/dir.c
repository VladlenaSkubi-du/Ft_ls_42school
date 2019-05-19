/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorwin <jcorwin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 16:50:56 by jcorwin           #+#    #+#             */
/*   Updated: 2019/05/19 05:51:58 by jcorwin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		print_inner(char *path, int *flags)
{
	*flags |= FLAG_N;
	ft_putchar('\n');
	print_dir(path, flags);
}

static void		get_files(t_stack *files, char *path, DIR *dir, int flags)
{
	t_file				*file;
	t_stack				*dirs;
	struct dirent		*entry;
	char				*tmp;

	dirs = ST_NEW();
	while ((entry = readdir(dir)))
	{
		if (*entry->d_name == '.')
			continue ;
		file = (t_file *)ft_xmalloc(sizeof(t_file));
		file->name = ft_strdup(entry->d_name);
		stat(file->name, &(file->buf));
		ST_ADD(files, file);
		if (opendir((tmp = ft_strrejoin(ft_strjoin(path, "/"), file->name))))
		{
			ST_ADD(dirs, tmp);
			ft_putendl(dirs->list->prev->data);
		}
		else
			free(tmp);

	}
	ST_SORT(files, files_sort(flags));
	ST_SORT(dirs, (int (*)(void *, void *))ft_strcmp);
	//print_files(files, flags);
	ST_ITER(dirs, (void (*)(void *, void *))print_inner, &flags, 0);
	ST_ITER(dirs, (void (*)(void *, void *))free_data, NULL, 0);
	ST_DEL(dirs);
}

// void			print_dir(t_file *dir_s, int *flags)
// {
// 	t_stack				*files;
// 	t_stack				*dirs;
// 	struct dirent		*entry;
// 	DIR					*dir;

// 	files = ST_NEW();
// 	dirs = ST_NEW();
// 	if (*flags & FLAG_N)
// 	{
// 		ft_putstr(dir_s->name);
// 		ft_putstr(":\n");
// 	}
// 	errno = 0;
// 	dir = opendir(dir_s->name);
// 	if (errno)
// 		return ;
// 	get_files(files, dirs, dir, *flags);
// 	ST_SORT(files, files_sort(*flags));
// 	print_files(files, *flags);
// 	if (*flags & FLAG_RR)
// 		ST_ITER(files, (void (*)(void *, void *))print_inner, flags, 0);
// 	ST_ITER(files, (void (*)(void *, void *))free_data, (void *)1, 0);
// 	ST_DEL(files);
// 	closedir(dir);
// }

void			print_dir(char *path, int *flags)
{
	t_stack				*files;
	struct dirent		*entry;
	DIR					*dir;

	files = ST_NEW();
	if (*flags & FLAG_N)
	{
		ft_putstr(path);
		ft_putstr(":\n");
	}
	errno = 0;
	dir = opendir(path);
	if (errno)
		return ;
	get_files(files, path, dir, *flags);
	ST_ITER(files, (void (*)(void *, void *))free_data, (void *)1, 0);
	ST_DEL(files);
	closedir(dir);
}
