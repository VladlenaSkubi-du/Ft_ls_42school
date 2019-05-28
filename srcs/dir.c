/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 16:50:56 by jcorwin           #+#    #+#             */
/*   Updated: 2019/05/28 16:05:32 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static char		*jjoin(char *path, char *name)
{
	return NULL;
}

static void		print_inner(t_file *file, int *flags)
{
	*flags |= FLAG_N;
	if ((file->info.st_mode & S_IFDIR) &&
					ft_strcmp(file->name, ".") && ft_strcmp(file->name, ".."))
	{
		buf_add("\n", 1);
		print_dir(file, flags);
	}
}

static void		read_file(struct dirent *entry,
									char *path, t_stack *files, int flags)
{
	t_file		*file;

//	if (*entry->d_name == '.' && !(flags & (FLAG_F | FLAG_A | FLAG_L)))
	if (*entry->d_name == '.' && !(flags & (FLAG_F | FLAG_A)))
		return ;
	file = (t_file *)ft_xmalloc(sizeof(t_file));
	file->name = ft_strdup(entry->d_name);
	if (flags & (FLAG_RR | FLAG_S | FLAG_SS | FLAG_U | FLAG_L | FLAG_T | FLAG_C))
	{
		file->path = ft_strrejoin(ft_strjoin(path, "/"), entry->d_name);
		if (!lstat(file->path, &file->info))
			ST_ADD(files, file);
		else
			del_file(file, NULL);
	}
	else
		ST_ADD(files, file);
}

void			print_dir(t_file *file, int *flags)
{
	t_stack				*files;
	struct dirent		*entry;
	char				*tmp;

	if (*flags & FLAG_N)
	{
		buf_add(file->path, ft_strlen(file->path));
		buf_add(":\n", 3);
	}
	if (!file->dir && !(file->dir = opendir(file->path)))
	{
		print_err(file->name);
		return ;
	}
	files = ST_NEW();
	while ((entry = readdir(file->dir)))
		read_file(entry, file->path, files, *flags);
	ST_SORT(files, files_sort(*flags));
	print_files(files, *flags);
	if (*flags & FLAG_RR)
		ST_ITER(files, (void (*)(void *, void *))print_inner,
											flags, *flags & FLAG_R);
	ST_ITER(files, (void (*)(void *, void *))del_file, NULL, 0);
	ST_DEL(files);
}
