/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorwin <jcorwin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 12:48:35 by jcorwin           #+#    #+#             */
/*   Updated: 2019/05/15 13:49:12 by jcorwin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		usage(void)
{
	ft_putendl("usage: ft_ls [1lrRatGpsufdgSCf] [file ...]");
	exit(0);
}

void		no_dir_or_file(char *dirname)
{
	ft_putstr("ft_ls: ");
	ft_putstr(dirname);
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

	i = 0;
	filenames = NULL;
	while (++i < argc)
	{
		if (*argv[i] == '-')
			*flags |= get_flags(argv[i]);
		else
			break ;
	}
	if (i < argc)
	{
		filenames = stack_init();
		while (i < argc)
			filenames->add(filenames, ft_strdup(argv[i++]));
	}
	if (filenames)
		filenames->sort(filenames, (int (*)(void *, void *))ft_strcmp);
	return (filenames);
}
