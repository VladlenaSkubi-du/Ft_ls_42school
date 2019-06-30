/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 12:48:35 by jcorwin           #+#    #+#             */
/*   Updated: 2019/06/30 14:58:26 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		allocate_by_flags_2(int *flags, int cur_flag)
{
	if (*flags & FLAG_C)
	{
		(cur_flag & FLAG_U) ? *flags ^= FLAG_C : *flags;
		if ((cur_flag & FLAG_C) && (*flags & FLAG_U))
			*flags ^= FLAG_U;
	}
	if (*flags & FLAG_FF)
	{
		(cur_flag & FLAG_P) ? *flags ^= FLAG_FF : *flags;
		if ((cur_flag & FLAG_FF) && (*flags & FLAG_P))
			*flags ^= FLAG_P;
	}
}

static void		allocate_by_flags_1(int *flags, int cur_flag)
{
	if (*flags & FLAG_F)
	{
		(*flags & FLAG_R) ? *flags ^= FLAG_R : *flags;
		(*flags & FLAG_A) ? *flags ^= FLAG_A : *flags;
		(*flags & FLAG_T) ? *flags ^= FLAG_T : *flags;
		(*flags & FLAG_SS) ? *flags ^= FLAG_SS : *flags;
	}
	// -l -g зависимость
	// обратить внимание на взаимоисключаемость -1 и -C и [-lg -> -1]
	if (*flags & FLAG_CC)
	{
		(cur_flag & FLAG_ONE) ? *flags ^= FLAG_CC : 0;
		if ((cur_flag & FLAG_CC) && (*flags & FLAG_ONE))
			*flags ^= FLAG_ONE;
		if ((cur_flag & FLAG_G) || (cur_flag & FLAG_L))
			*flags ^= FLAG_CC;
		if ((cur_flag & FLAG_CC) && (*flags & FLAG_G))
			*flags ^= FLAG_G;
		if ((cur_flag & FLAG_CC) && (*flags & FLAG_L))
			*flags ^= FLAG_L;
	}
	if ((*flags & FLAG_C) || (*flags & FLAG_FF))
		allocate_by_flags_2(flags, cur_flag);
}

// Проблема:
// at-e4% ./ft_ls -Fl
// ft_ls: illegal option -- l
// usage: ft_ls [-1lrRatGpsufdgSCcF] [file ...]

static void		get_flags(char *arg, int *flags)
{
	int			i;

	++arg;
	while (*arg && (i = ft_strchri("1lrRatGpsufdgSCcF-", *arg)) != -1)
	{
		*flags |= 1 << i;
		allocate_by_flags_1(flags, 1 << i);
		++arg;
		if (*flags & FLAG_MINUS)
			break ;
	}
	if (*arg)
	{
		buf_err("ft_ls: illegal option -- ");
		ft_printerr(arg, 1);
		buf_err("\n");
		usage();
	}
}

t_stack			*get_args(int *flags, int argc, char **argv)
{
	int			i;
	t_stack		*filenames;
	t_file		*file;

	i = 0;
	filenames = NULL;
	while (++i < argc)
		if (*argv[i] == '-' && !(*flags & FLAG_MINUS))
			get_flags(argv[i], flags);
		else
			break ;
	if (i < argc)
	{
		*flags |= (argc - i > 1) ? FLAG_FOLDER_RR : 0;
		filenames = ST_NEW();
		while (i < argc)
		{
			ST_ADD(filenames, (file = (t_file *)ft_xmalloc(sizeof(t_file))));
			file->name = ft_strdup(argv[i++]);
			file->path = ft_strdup(file->name);
		}
	}
	if (filenames)
		ST_SORT(filenames, files_sort(0));
	return (filenames);
}
