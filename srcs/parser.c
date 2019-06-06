/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 12:48:35 by jcorwin           #+#    #+#             */
/*   Updated: 2019/06/06 18:23:28 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int		allocate_by_flags_2(int flags, int cur_flag)
{
	if (flags & FLAG_C)
	{
		(cur_flag & FLAG_U) ? flags ^= FLAG_C : flags;
		if ((cur_flag & FLAG_C) && (flags & FLAG_U))
			flags ^= FLAG_U;
	}
	if (flags & FLAG_FF)
	{
		(cur_flag & FLAG_P) ? flags ^= FLAG_FF : flags;
		if ((cur_flag & FLAG_FF) && (flags & FLAG_P))
			flags ^= FLAG_P;
	}
	return (flags);
}

static int		allocate_by_flags_1(int flags, int cur_flag)
{
	if (flags & FLAG_F)
	{
		(flags & FLAG_R) ? flags ^= FLAG_R : flags;
		(flags & FLAG_A) ? flags ^= FLAG_A : flags;
		(flags & FLAG_T) ? flags ^= FLAG_T : flags;
		(flags & FLAG_SS) ? flags ^= FLAG_SS : flags;
	}
	if (flags & FLAG_CC)
	{
		(cur_flag & FLAG_ONE) ? flags ^= FLAG_CC : flags;
		if ((cur_flag & FLAG_CC) && (flags & FLAG_ONE))
			flags ^= FLAG_ONE;
		if ((cur_flag & FLAG_L) || (cur_flag & FLAG_G))
			flags ^= FLAG_CC;
		if ((cur_flag & FLAG_CC) && (flags & FLAG_L))
			flags ^= FLAG_L;
		if ((cur_flag & FLAG_CC) && (flags & FLAG_G))
			flags ^= FLAG_G;
	}
	if ((flags & FLAG_C) || (flags & FLAG_FF))
		flags = allocate_by_flags_2(flags, cur_flag);
	return (flags);
}

static int		get_flags(char *arg)
{
	int			flags;
	int			i;

	flags = 0;
	++arg;
	while (*arg && (i = ft_strchri("1lrRatGpsufdgSCc-F", *arg)) != -1)
	{
		flags |= 1 << i;
		if (flags & FLAG_G)
			flags |= FLAG_L;
		flags = allocate_by_flags_1(flags, 1 << i);
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

t_stack			*get_args(int *flags, int argc, char **argv)
{
	int			i;
	t_stack		*filenames;
	t_file		*file;

	i = 0;
	filenames = NULL;
	while (++i < argc) //how it works without {}
		if (*argv[i] == '-' && !(*flags & FLAG_MINUS))
			*flags |= get_flags(argv[i]);
		else
			break ;
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
