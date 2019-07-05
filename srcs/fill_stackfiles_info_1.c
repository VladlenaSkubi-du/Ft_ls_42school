/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_stackfiles_info_1.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 19:15:40 by sschmele          #+#    #+#             */
/*   Updated: 2019/07/05 13:59:58 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		find_width(int len, int *columns)
{
	*columns = len > *columns ? len : *columns;
}

/*
**As for column[10] - it is necessary ot get the maximal file name before it is
**changed in the change_name function.
*/

static void		fill_info_2(t_file *file, int *col)
{
	if (col[5])
	{
		file->uid = getpwuid(file->info.st_uid);
		if (file->uid == NULL)
		{
			perror("getpwuid");
			exit(1);
		}
		find_width(ft_strlen(file->uid->pw_name), &col[5]);
	}
	if (col[6])
	{
		file->gid = getgrgid(file->info.st_gid);
		if (file->gid == NULL)
		{
			perror("getgrgid");
			exit(1);
		}
		find_width(ft_strlen(file->gid->gr_name), &col[6]);
	}
	(col[8]) ? fill_time(file, col) : 0;
	(col[0] & FLAG_CC) ? find_width(ft_strlen(file->name), &col[10]) : 0;
	((col[0] & FLAG_GG) && (col[0] & FLAG_ATTY)) ? color_stackfiles(file) : 0;
	change_name(file, col[0]);
}

/*
**If the column is turned on - the information in t_file is filled and
**maximal length of the string among all the files in the directory is
**calculated.
*/

static void		fill_info_1(t_file *file, int *columns)
{
	columns[1] += file->info.st_blocks;
	if (columns[2])
	{
		file->total = ft_utoa_base(file->info.st_blocks, 10);
		find_width(ft_strlen(file->total), &columns[2]);
	}
	(columns[3]) || (columns[0] & (FLAG_GG | FLAG_FF)) ? fill_mode(file) : 0;
	if (columns[4])
	{
		file->link = ft_utoa_base(file->info.st_nlink, 10);
		find_width(ft_strlen(file->link), &columns[4]);
	}
	if (columns[7])
	{
		if (file->type == 'b' || file->type == 'c')
			fill_minmaz(file);
		else
			file->size = ft_utoa_base(file->info.st_size, 10);
		find_width(ft_strlen(file->size), &columns[7]);
	}
	fill_info_2(file, columns);
}

/*
**Turn on or off of the columns with information - is needed for -l, -g, -s and
**-C-flags output - if the column[n] is turned on, information will be filled
**in the fill_info_1 function.
*/

static void		width_init(int *columns, int flags)
{
	int		i;

	i = 2;
	if (!flags)
		flags |= FLAG_MINUS;
	columns[0] = flags;
	if (flags & FLAG_S)
		columns[2] = 1;
	if (flags & (FLAG_L | FLAG_G))
	{
		while (++i < 8)
			columns[i] = 1;
		columns[3] = 11;
		columns[8] = 12;
	}
	if (flags & FLAG_G)
		columns[5] = 0;
	if (flags & FLAG_CC)
		columns[10] = 1;
}

/*
**In the array of ints called columns, there are the following values:
**columns[0] = flags (masks defined in ./includes/ft_ls.h);
**
**columns[1] = general total as int - the sum of all the 512-bytes blocks that
**the directory occupies;
**
**columns[2] = maximal length of the string with INDIVIDUAL TOTAL (in chars)
**from all the files in the directory - the sum of 512-bytes blocks that
**the file in the directory occupies (for output use ./ft_ls -s);
**
**columns[3] = standard length of MODE (11 chars) that consists of the:
**file-type + rwx-access for the user + rwx-access for the group +
**rwx-access for the others + acl-access ("@" or "+" or " ");
**
**columns[4] = maximal length of the string with the number of hard LINKS;
**
**columns[5] = maximal length of the string with the UID-name;
**
**columns[6] = maximal length of the string with the GID-name;
**
**columns[7] = maximal length of the string with the SIZE in bytes of all the
**file types except of devices: for block or symbolic devices in this
**column we keep maximal length of the string with MAJOR AND MINOR like:
**"[major number], [minor number]";
**
**columns[8] = standard length of TIME (12 chars),
**can be: time of last modification or last access or last status change;
**
**columns[9] = length of terminal or file for C-flag with output in columns;
**
**columns[10] = maximal length of the string with name (+other parameters)
**for C-flag - to define maximal length of each output-column.
**
**The function is called several times for each directory but
**initialization of columns array is needed only one time.
*/

void			fill_and_print_stackfiles(t_stack *files, int *flags, int total)
{
	static int		columns[11];

	if (!columns[0])
		width_init(columns, *flags);
	if (*flags & (FLAG_L | FLAG_S | FLAG_G | FLAG_GG | FLAG_P |
				FLAG_FF | FLAG_CC))
		files->iter(files, (void (*)(void *, void *))fill_info_1,
				columns, *flags & FLAG_R);
	separate_output(flags, columns);
	if ((*flags & (FLAG_L | FLAG_G | FLAG_S)) && ~*flags & FLAG_D && total)
	{
		buf_add("total ", 6);
		buf_add_num(columns[1]);
		buf_add("\n", 1);
	}
	columns[8] = (*flags & FLAG_CC) ? files->size : columns[8];
	columns[7] = (*flags & FLAG_CC) ? columns[2] : columns[7];
	if (*flags & FLAG_CC)
		files->iter(files, (void (*)(void *, void *))buf_col,
				&columns[7], *flags & FLAG_R);
	else
		files->iter(files, (void (*)(void *, void *))print_stackfile,
			columns, *flags & FLAG_R);
	ft_bzero(columns, sizeof(int) * 11);
}
