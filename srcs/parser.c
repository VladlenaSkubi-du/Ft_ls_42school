/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorwin <jcorwin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 12:48:35 by jcorwin           #+#    #+#             */
/*   Updated: 2019/07/05 14:24:20 by sschmele         ###   ########.fr       */
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
	if (*flags & FLAG_ONE)
	{
		(cur_flag & FLAG_L) ? *flags ^= FLAG_ONE : 0;
		(cur_flag & FLAG_G) ? *flags ^= FLAG_ONE : 0;
		if ((cur_flag & FLAG_ONE) && (*flags & FLAG_G))
			*flags ^= FLAG_G;
		if ((cur_flag & FLAG_ONE) && (*flags & FLAG_L))
			*flags ^= FLAG_L;
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
	if ((*flags & FLAG_C) || (*flags & FLAG_FF) || (*flags & FLAG_ONE))
		allocate_by_flags_2(flags, cur_flag);
}

static void		get_flags(char *arg, int *flags, char *program)
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
		buf_err(program);
		buf_err(": illegal option -- ");
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
			get_flags(argv[i], flags, argv[0]);
		else
			break ;
	if (i < argc)
	{
		*flags |= (argc - i > 1) ? FLAG_FOLDER_RR : 0;
		filenames = stack_init();
		while (i < argc)
		{
			filenames->add(filenames, (file = (t_file *)
						ft_xmalloc(sizeof(t_file))));
			file->name = ft_strdup(argv[i++]);
			file->path = ft_strdup(file->name);
		}
	}
	(filenames) ? filenames->sort(filenames, files_sort(0)) : 0;
	return (filenames);
}
