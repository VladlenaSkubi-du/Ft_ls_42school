/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 02:00:05 by jcorwin           #+#    #+#             */
/*   Updated: 2019/05/28 13:49:26 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		print_file(t_file *file, int *flags)
{
	buf_add(file->name, ft_strlen(file->name));
	buf_add("\n", 1);
}

static void		fill_info(t_file *file, int *columns) //разделить под флаги и изменить под строку
{
	char			*tmp_time;
	time_t			time_sec;

	file->uid = getpwuid(file->info.st_uid);
	file->gid = getgrgid(file->info.st_gid);
	file->link = ft_utoa_base(file->info.st_nlink, 10); //переделать под другую функцию
	file->size = ft_utoa_base(file->info.st_size, 10);//переделать под другую функцию
	if (columns[0] & (FLAG_L | FLAG_U))
		time_sec = file->info.st_atime;
	else if (columns[0] & (FLAG_L | FLAG_C))
		time_sec = file->info.st_ctime;
	else
		time_sec = file->info.st_mtime;
	file->time = (char*)ft_xmalloc(12);
//	tmp_time = ft_strdup(ctime(&time_sec));
	tmp_time = ctime(&time_sec);
	file->time = ft_strncpy(file->time, &(tmp_time[4]), 6);
	if ((time(NULL) - time_sec) < (31556926 / 2))
		file->time = ft_strncat(file->time, &(tmp_time[10]), 6);
	else
	{
		file->time[6] = ' ';
		file->time = ft_strncat(file->time, &(tmp_time[19]), 5);
	}
	printf("%s\n%s\n", file->name, file->time);
}

void			print_files(t_stack *files, int flags)
{
	int			columns[6];

	columns[0] = flags;
	ST_ITER(files, (void (*)(void *, void *))fill_info, &columns, flags & FLAG_R);
//	ST_ITER(files, (void (*)(void *, void *))print_file, &flags, flags & FLAG_R);
}

