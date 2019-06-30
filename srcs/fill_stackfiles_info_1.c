/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_stackfiles_info_1.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorwin <jcorwin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 19:15:40 by sschmele          #+#    #+#             */
/*   Updated: 2019/06/30 19:06:39 by jcorwin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		find_width(int len, int *columns)
{
	*columns = len > *columns ? len : *columns;
}

static void		fill_info_2(t_file *file, int *col)
{
	// char		*arr[3];
	
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
	if (col[8])
		fill_time(file, col);
	(col[0] & FLAG_CC) ? find_width(ft_strlen(file->name), &col[10]) : 0; // узнаем длину до изменения имени ссылки или Ф и п флагов
	if (col[0] & FLAG_GG)
	{
		// ft_strcpy(file->color, "\033[37;40m");
		color_stackfiles(file);
		// file->name = ft_strjoin(file->color, ft_strrejoin(file->name, "\033[0m"));
		file->name = ft_strrejoin(file->name, "\033[0m");
	}
	change_name(file, col[0]);	
}

static void		fill_info_1(t_file *file, int *columns)
{
	columns[1] += file->info.st_blocks;
	if (columns[2]) 
	{
		file->total = ft_utoa_base(file->info.st_blocks, 10);
		find_width(ft_strlen(file->total), &columns[2]);
	}
	(columns[3]) || (columns[0] & (FLAG_GG | FLAG_FF)) ? fill_mode(file) : 0;
	// (columns[3]) || (columns[0] & (FLAG_L | FLAG_G)) ?
	// 	find_width(ft_strlen(file->mode), &columns[3]) : 0;
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

static void		width_init(int *columns, int flags)
{
	// column 10 нужен с -С
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
	// if (flags & (FLAG_GG | FLAG_FF))
	// 	columns[3] = 0;
	if (flags & FLAG_CC)
		columns[10] = 1;
}

void			fill_and_print_stackfiles(t_stack *files, int *flags, int total)
{
	static int		columns[11];
	/// изменить: минор/размер вместе, сдвинуть, 10 - name
	//0 - флаги, 1 - общий total, 2 - индивидуальный total, 3 - доступ, 4 - ссылки,
	//5 - uid, 6 - gid, 7 - мажор и минор для устройств или размер, 8 - время,
	//9 - ширина терминала, 10 - максимальная ширина строки (вместе с пробелами)
	if (!columns[0]) //функция вызывается много раз, а инициализация нужна 1 раз
		width_init(columns, *flags);
	if (*flags & (FLAG_L | FLAG_S | FLAG_G | FLAG_GG | FLAG_P | FLAG_FF | FLAG_CC))
		ST_ITER(files, (void (*)(void *, void *))fill_info_1,
				columns, *flags & FLAG_R);
	separate_output(*flags, columns);
	if ((*flags & FLAG_L) && ~*flags & FLAG_D && total)
	{
		buf_add("total ", 6);
		buf_add_num(columns[1]);
		buf_add("\n", 1);
	}
	if (*flags & FLAG_CC)
	{
		columns[8] = files->size;
		ST_ITER(files, (void (*)(void *, void *))buf_col,
			&columns[8], *flags & FLAG_R);
	}
	else
		ST_ITER(files, (void (*)(void *, void *))print_stackfile,
			columns, *flags & FLAG_R);
}