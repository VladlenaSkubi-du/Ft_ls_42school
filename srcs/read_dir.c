/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorwin <jcorwin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 16:50:56 by jcorwin           #+#    #+#             */
/*   Updated: 2019/07/01 21:11:52 by jcorwin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		fill_type_entry(unsigned char entry, t_file *file)
{
	if (entry == DT_BLK)
		file->type = 'b';
	else if (entry == DT_CHR)
		file->type = 'c';
	else if (entry == DT_DIR)
		file->type = 'd';
	else if (entry == DT_REG)
		file->type = '-';
	else if (entry == DT_FIFO)
		file->type = 'p';
	else if (entry == DT_LNK)
		file->type = 'l';
	else if (entry == DT_UNKNOWN)
		file->type = 'd';
	else if (entry == DT_SOCK)
		file->type = 's';
}

static void		print_inner(t_file *file, int *flags)
{
	*flags |= FLAG_FOLDER_RR;
	if ((file->info.st_mode & S_IFDIR) &&
					ft_strcmp(file->name, ".") && ft_strcmp(file->name, ".."))
	{
		buf_add("\n", 1);
		print_dir(file, flags);
	}
}

static void		read_file(struct dirent *entry,
									char *path, t_stack *files, int *flags)
{
	t_file				*file;

	if (*entry->d_name == '.' && !(*flags & (FLAG_F | FLAG_A)))
		return ;
	file = (t_file *)ft_xmalloc(sizeof(t_file));
	file->name = ft_strdup(entry->d_name);
	if (*flags & (FLAG_RR | FLAG_S | FLAG_SS | FLAG_U | FLAG_L |
				FLAG_T | FLAG_C | FLAG_P | FLAG_GG | FLAG_FF | FLAG_G))
	{
		if (*flags & (FLAG_L | FLAG_G | FLAG_P | FLAG_FF | FLAG_GG))
			fill_type_entry(entry->d_type, file);
		file->path = ft_strrejoin(ft_strjoin(path, "/"), entry->d_name);
		if (!lstat(file->path, &file->info))
			files->add(files, file);
		else
			del_file(file, NULL);
	}
	else
		files->add(files, file);
	//возможно, нужно чистить здесь файл, потому что ты тут маллочишь его (и все составляющие) - но просто использовать del_file не получится - я пробовала
}

void			print_dir(t_file *file, int *flags)
{
	t_stack				*files;
	struct dirent		*entry;

	if (*flags & FLAG_FOLDER_RR)
	{
		buf_add(file->path, ft_strlen(file->path));
		buf_add(":\n", 2);
	}
	if (!file->dir && !(file->dir = opendir(file->path)))
	{
		print_err(file->name);
		return ;
	}
	files = stack_init();
	while ((entry = readdir(file->dir)))
		read_file(entry, file->path, files, flags);
	files->sort(files, files_sort(*flags));
	fill_and_print_stackfiles(files, flags, files->size ? 1 : 0);
	if (*flags & FLAG_RR)
		files->iter(files, (void (*)(void *, void *))print_inner,
											flags, *flags & FLAG_R);
	files->iter(files, (void (*)(void *, void *))del_file, NULL, 0);
	files->del(files);
}
