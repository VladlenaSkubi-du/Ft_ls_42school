/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorwin <jcorwin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 10:50:06 by sschmele          #+#    #+#             */
/*   Updated: 2019/05/13 19:51:40 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <dirent.h>

#include "ft_ls.h"

static void putFileName(t_file *file)
{
	ft_putnbr(file->fromstart);
	ft_putstr(" - ");
	ft_putendl(file->name);
}

void	print_dir(char *dirname)
{
	t_param			param;
	DIR				*dir;
	struct dirent	*entry;

	ft_bzero(&param, sizeof(param));
	dir = opendir(dirname);
	if (!dir)
	{
		perror("diropen");
		exit(1);
	}

	while ((entry = readdir(dir)))
	{
		param.file = file_new(param.file);
		param.file->prev->name = entry->d_name;
		stat(entry->d_name, &(param.file->prev->buf));
	}
	file_count(param.file);
	write(1, "\n\n", 2);
	quickSort(param.file, param.file, param.file->prev, file_strcmp);
	file_foreach(param.file, putFileName);
	file_del(param.file);
	closedir(dir);
}

int		main(int argc, char **argv)
{
	int		i;
	int		flags;

	flags = 0;
	i = get_args(&flags, argc, argv);
	while (i < argc)
		print_dir(argv[i++]);
	return (0);
}
