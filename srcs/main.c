/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorwin <jcorwin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 10:50:06 by sschmele          #+#    #+#             */
/*   Updated: 2019/05/14 20:03:55 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <dirent.h>

#include "ft_ls.h"

static void print_inner(t_file *file, int flags);

static void putFileName(t_file *file)
{
	ft_putnbr(file->fromstart);
	ft_putstr(" - ");
	ft_putendl(file->name);
}

static void print_inner(t_file *file, int flags)
{
	if (ft_strcmp(file->name, "..") && ft_strcmp(file->name, ".")
			&& file->buf.st_mode & S_IFDIR)
	{
		ft_putstr(file->name);
		ft_putstr(":\n");
		//		print_dir(file->name, flags);
		ft_putendl("");
	}
}

void		print_dir(t_param param, int flags)
{
	file_foreach(param.file, putFileName);
}

void		check_dir(char *dirname, char **not_dir, int flags, t_param *param)
{
	DIR				*dir;
	
	dir = opendir(dirname);
	if (errno == ENOENT)
		no_dir_or_file(dirname);
	else if (errno == ENOTDIR)
	{
		*not_dir = ft_strrejoin(*not_dir, dirname);
		*not_dir = ft_strrejoin(*not_dir, "\n");
	}
	else
		workover_dir(dir, flags, param);
}

void		workover_dir(DIR *dir, int flags, t_param *param)
{
	struct dirent	*entry;

	while ((entry = readdir(dir)))
	{
		if (((flags >> 4) & 1) == 0)
			if (*entry->d_name == '.')
				continue ;
		param->file = file_new(param->file);
		param->file->prev->name = entry->d_name;
		stat(entry->d_name, &(param->file->prev->buf));
	}
	file_count(param->file);
	if (param->file->prev->fromstart > 2)
		quick_sort_list(param->file, param->file, param->file->prev, file_strcmp);
	param->file = file_slip(param->file, file_strcmp);
	//	file_foreach(param.file, print_inner);
	closedir(dir);
}

int			main(int argc, char **argv)
{
	int				flags;
	int				i;
	t_param			param;
	char			*not_dir;

	flags = 0;
	i = get_args(&flags, argc, argv);
	ft_bzero(&param, sizeof(param));
	not_dir = (char*)ft_xmalloc(1);
	if (i == argc)
		workover_dir(opendir("."), flags, &param);
	else
	{
		quick_mas_sort(&argv[i], 0, argc - i - 1);
		while (i < argc)
			check_dir(argv[i++], &not_dir, flags, &param);
		if (not_dir[0])
			ft_putstr(not_dir);
	}
	if (param.file)
		print_dir(param.file, flags);
	file_del(param.file);
	free(not_dir);
	return (0);
}
