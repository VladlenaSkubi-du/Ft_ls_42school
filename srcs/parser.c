/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorwin <jcorwin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 12:48:35 by jcorwin           #+#    #+#             */
/*   Updated: 2019/06/05 21:51:07 by jcorwin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int		chec_flags(int flags, int current_flag)
{
	
}

static int		get_flags(char *arg)
{
	int		flags;
	int		i;

	flags = 0;
	++arg;
	while (*arg && (i = ft_strchri("1lrRatGpsufdgSCc-F", *arg)) != -1)
	{
		flags |= 1 << i;
		if (flags & FLAG_G)
			flags |= FLAG_L;
		// новая фунцкия flags = check_flags(flags, 1 << i);
		++arg;
		if (flags & FLAG_MINUS)
			break ;
	}
	if (*arg)
	{
		buf_err("ft_ls: illegal option -- ");
		ft_printerr(arg, 1);
		buf_err("\n");
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
		if (*argv[i] == '-' && !(*flags & FLAG_MINUS))
			*flags |= get_flags(argv[i]);
		else
			break ;
	if ((*flags & FLAG_F) && (*flags & FLAG_R))
		*flags ^= FLAG_R;
	if (i < argc)
	{
		*flags |= (argc - i > 1) ? FLAG_FOLDER_RR : 0;
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
