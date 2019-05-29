/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorwin <jcorwin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 02:00:05 by jcorwin           #+#    #+#             */
/*   Updated: 2019/05/29 13:38:53 by jcorwin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		fill_info(t_file *file, int *columns);
static void		find_length(t_file file, int *columns);

static void		print_file(t_file *file, int *col)
{
	int		i;
	void	**ptr;

	i = 0;
	ptr = (void **)&file->uid;
	while (++i < 7)
		if (col[i])
		{
			if (i > 2)
				buf_fill(*ptr, ft_strlen(*ptr), col[i], 0);
			else if (i == 2)
				buf_fill(((struct passwd *)*ptr)->pw_name,
				ft_strlen(((struct passwd *)*ptr)->pw_name), col[i], 1);
			else if (i == 3)
				buf_fill(((struct group *)*ptr)->gr_name,
				ft_strlen(((struct group *)*ptr)->gr_name), col[i], 1);
			++ptr;
			if ((i == 1 && col[1] == 11) || i > 5)
				buf_add(" ", 1);
			else
				buf_add("  ", 2);
		}
	buf_add(file->name, ft_strlen(file->name));
	buf_add("\n", 1);
}

static void		fill_info(t_file *file, int *columns)
{
	char			*tmp_time;
	time_t			time_sec;

	file->uid = getpwuid(file->info.st_uid);
	file->gid = getgrgid(file->info.st_gid);
	file->link = ft_utoa_base(file->info.st_nlink, 10); //переделать под другую функцию
	file->size = ft_utoa_base(file->info.st_size, 10); //переделать под другую функцию
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
//	printf("name: %s\n", file->name);
	find_length(*file, &columns[1]);
	// printf("flags: %d link: %d uid: %d	gid: %d	size: %d name: %d\n", columns[0], columns[1], columns[2], columns[3], columns[4], columns[5]);
}

static void		find_length(t_file file, int *columns)
{
	int			tmp;

	tmp = ft_strlen(file.link);
	columns[0] = (tmp > columns[0]) ? tmp : columns[0];
	tmp = ft_strlen(file.uid->pw_name);
	columns[1] = (tmp > columns[1]) ? tmp : columns[1];
	tmp = ft_strlen(file.gid->gr_name);
	columns[2] = (tmp > columns[2]) ? tmp : columns[2];
	tmp = ft_strlen(file.size);
	columns[3] = (tmp > columns[3]) ? tmp : columns[3];
	tmp = ft_strlen(file.name);
	columns[4] = (tmp > columns[4]) ? tmp : columns[4];
}

void			print_files(t_stack *files, int flags)
{
	static int	columns[6]; //можно ли? mozhno

	columns[0] = flags;
	ST_ITER(files, (void (*)(void *, void *))fill_info, &columns, flags & FLAG_R);
	ST_ITER(files, (void (*)(void *, void *))print_file, columns, flags & FLAG_R);
}

