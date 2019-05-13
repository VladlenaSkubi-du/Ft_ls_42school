/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorwin <jcorwin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 12:48:35 by jcorwin           #+#    #+#             */
/*   Updated: 2019/05/13 19:55:24 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		usage(void)
{
	ft_putendl("usage: ft_ls [-1lrRatGps] [file ...]");
	exit(0);
}

int			get_flags(char *arg)
{
	int		flags;
	int		i;

	flags = 0;
	while ((i = ft_strchri("1lrRatGps", *(++arg))) != -1)
		flags |= 1 << i;
	if (*arg)
	{
		ft_putstr("ft_ls: illegal option -- ");
		ft_putchar(*arg);
		ft_putchar('\n');
		usage();
	}
	return (flags);
}

int			get_args(int *flags,  int argc, char **argv)
{
	int		i;

	i = 0;
	while (++i < argc)
	{
		if (*argv[i] == '-')
			*flags |= get_flags(argv[i]);
		else
			break ;

	}
	return (i);
}
