/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorwin <jcorwin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 12:48:35 by jcorwin           #+#    #+#             */
/*   Updated: 2019/05/27 19:33:36 by jcorwin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		usage(void)
{
	ft_putendl("usage: ft_ls [1lrRatGpsufdgSCf] [file ...]");
	exit(0);
}

void			print_err(char *dirname)
{
	// ЗАМЕНИТЬ НА ВТОРОЙ ПОТОК!!!
	ft_putstr("ft_ls: ");
	ft_putstr(dirname);
	if (errno == EACCES)
		ft_putendl(": Permission denied");
	else if (errno == ENOENT)
		ft_putendl(": No such file or directory");
}
static int		get_flags(char *arg)
{
	int		flags;
	int		i;

	flags = 0;
	++arg;
	while (*arg && (i = ft_strchri("1lrRatGpsufdgSCf", *arg)) != -1)
	{
		flags |= 1 << i;
		++arg;
	}
	if (*arg)
	{
		ft_putstr("ft_ls: illegal option -- ");
		ft_putchar(*arg);
		ft_putchar('\n');
		usage();
	}
	return (flags);
}

t_stack			*get_args(int *flags,  int argc, char **argv)
{
	int			i;
	t_stack		*filenames;
	t_file		*file;

	i = 0;
	filenames = NULL;
	while (++i < argc)
		if (*argv[i] == '-')
			*flags |= get_flags(argv[i]);
		else
			break ;
	if ((*flags & FLAG_F) && (*flags & FLAG_R))
		*flags ^= FLAG_R;
	if (i < argc)
	{
		*flags |= (argc - i > 1) ? FLAG_N : 0;
		filenames = ST_NEW();
		while (i < argc)
		{
			file = (t_file *)ft_xmalloc(sizeof(t_file));
			file->name = ft_strdup(argv[i++]);
			file->path = ft_strdup(file->name);
			ST_ADD(filenames, file);
		}
	}
	if (filenames)
		ST_SORT(filenames, files_sort(0));
	return (filenames);
}
