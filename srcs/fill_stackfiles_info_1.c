/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_stackfiles_info_1.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorwin <jcorwin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 19:15:40 by sschmele          #+#    #+#             */
/*   Updated: 2019/06/05 21:50:36 by jcorwin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		fill_mode(t_file *file)
{
	mode_t			m;

	m = file->info.st_mode;
	file->mode = ft_xmalloc(sizeof(char) * 12);
	file->mode[0] = file->type;
	file->mode[1] = ((m & 00400) && (m & 00700)) ? 'r' : '-';
	file->mode[2] = ((m & 00200) && (m & 00700)) ? 'w' : '-';
	file->mode[3] = ((m & 00100) && (m & 00700)) ? 'x' : '-';
	file->mode[4] = ((m & 00040) && (m & 00070)) ? 'r' : '-';
	file->mode[5] = ((m & 00020) && (m & 00070)) ? 'w' : '-';
	file->mode[6] = ((m & 00010) && (m & 00070)) ? 'x' : '-';
	file->mode[7] = ((m & 00004) && (m & 00007)) ? 'r' : '-';
	file->mode[8] = ((m & 00002) && (m & 00007)) ? 'w' : '-';
	file->mode[9] = ((m & 00001) && (m & 00007)) ? 'x' : '-';
	file->mode[3] = ((m & 04000) && file->mode[3] == 'x') ? 's' : file->mode[3];
	file->mode[6] = ((m & 02000) && file->mode[6] == 'x') ? 's' : file->mode[6];
	file->mode[9] = ((m & 01000) && file->mode[9] == 'x') ? 't' : file->mode[9];
	file->mode[3] = ((m & 04000) && file->mode[3] == '-') ? 'S' : file->mode[3];
	file->mode[6] = ((m & 02000) && file->mode[6] == '-') ? 'S' : file->mode[6];
	file->mode[9] = ((m & 01000) && file->mode[9] == '-') ? 'T' : file->mode[9];
	get_acl(file);
}

static void		fill_time(t_file *file, int *columns)
{
	char			*tmp_time;
	time_t			time_sec;

	if ((columns[0] & FLAG_L) && (columns[0] & FLAG_U))
		time_sec = file->info.st_atime;
	else if ((columns[0] & FLAG_L) && (columns[0] & FLAG_C))
		time_sec = file->info.st_ctime;
	else
		time_sec = file->info.st_mtime;
	file->time = (char*)ft_xmalloc(12);
	tmp_time = ctime(&time_sec);
	file->time = ft_strncpy(file->time, &(tmp_time[4]), 6);
	if ((time(NULL) - time_sec) < (31556926 / 2))
		file->time = ft_strncat(file->time, &(tmp_time[10]), 6);
	else
	{
		file->time[6] = ' ';
		file->time = ft_strncat(file->time, &(tmp_time[19]), 5);
	}
}

static void		fill_info(t_file *file, int *columns)
{
	columns[1] += file->info.st_blocks;
	file->total = ft_utoa_base(file->info.st_blocks, 10);
	file->uid = getpwuid(file->info.st_uid);
	if (file->uid == NULL)
	{
		perror("getpwuid");
		exit(1);
	}
	file->gid = getgrgid(file->info.st_gid);
	if (file->gid == NULL)
	{
		perror("getgrgid");
		exit(1);
	}
	file->link = ft_utoa_base(file->info.st_nlink, 10);
	file->size = ft_utoa_base(file->info.st_size, 10);
	fill_time(file, columns);
	fill_mode(file);
	if (file->type == 'l')
		fill_link(file);
	fill_minmaz(file);
	find_length(file, columns);
}

static void		width_init(int *columns, int flags)
{
	int		i;

	i = 2;
	if (!flags)
		flags |= FLAG_MINUS;
	columns[0] = flags;
	if (flags & FLAG_S)
		columns[2] = 1;
	if (flags & (FLAG_L))
	{
		while (++i < 11)
			columns[i] = 1;
		columns[3] = 11;
		columns[10] = 12;
	}
	if (flags & FLAG_G)
		columns[5] = 0;
}

void			fill_and_print_stackfiles(t_stack *files, int *flags)
{
	static int		columns[11];

	//0 - флаги, 1 - общий total, 2 - индивидуальный total, 3 - доступ, 4 - ссылки,
	//5 - uid, 6 - gid, 7 - мажор для устройств, 8 - минор для устройств,
	//9 - размер, 10 - время.
	if (!columns[0])
		width_init(columns, *flags);
	if (*flags & (FLAG_L))
	{
		/// эти комменты можно удалить 
		// if (*flags & (FLAG_DEVICE))
		// {
		// 	columns[7] = 1;
		// 	columns[8] = 1;
		// 	columns[9] = 0;
		// }
		// else
		// {
		// 	columns[7] = 0;
		// 	columns[8] = 0;
		// 	columns[9] = 1;
		// }
		columns[7] = *flags & FLAG_DEVICE ? 1 : 0;
		columns[8] = *flags & FLAG_DEVICE ? 1 : 0;
		columns[9] = *flags & FLAG_DEVICE ? 0 : 1;
		ST_ITER(files, (void (*)(void *, void *))fill_info,
				columns, *flags & FLAG_R);
	}
	if (*flags & FLAG_L)
	{
		buf_add("total ", 6);
		buf_add_num(columns[1]);
		buf_add("\n", 1);
	}
	ST_ITER(files, (void (*)(void *, void *))print_stackfile,
			columns, *flags & FLAG_R);
	if (*flags & FLAG_DEVICE)
		*flags ^= FLAG_DEVICE;
}
