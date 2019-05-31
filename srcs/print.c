/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 02:00:05 by jcorwin           #+#    #+#             */
/*   Updated: 2019/05/31 13:50:42 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		fill_info(t_file *file, int *columns);
static void		fill_time(t_file *file, int *columns);
static char		*fill_mode(t_file *file);
static void		fill_link(t_file *file);
static void		find_length(t_file file, int *columns);

static void		print_file(t_file *file, int *col)
{
	/*int		i;
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
	buf_add("\n", 1);*/
	printf("%s %3s %s  %s  %5s %s %s\n", file->mode, file->link, file->uid->pw_name, file->gid->gr_name, file->size, file->time, file->name);
}

static void		fill_info(t_file *file, int *columns)
{
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
	file->link = ft_utoa_base(file->info.st_nlink, 10); //переделать под другую функцию
	file->size = ft_utoa_base(file->info.st_size, 10); //переделать под другую функцию
	fill_time(file, columns);
	file->mode = ft_strdup(fill_mode(file));
	if (file->type == 'l')
		fill_link(file);
	find_length(*file, &columns[1]);
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

static char		*fill_mode(t_file *file)
{
	static char		mode[11];
	mode_t			m;

	m = file->info.st_mode;
	mode[0] = file->type;	
	mode[1] = ((m & 00400) && (m & 00700)) ? 'r' : '-';
	mode[2] = ((m & 00200) && (m & 00700)) ? 'w' : '-';
	mode[3] = ((m & 00100) && (m & 00700)) ? 'x' : '-';
	mode[4] = ((m & 00040) && (m & 00070)) ? 'r' : '-';
	mode[5] = ((m & 00020) && (m & 00070)) ? 'w' : '-';
	mode[6] = ((m & 00010) && (m & 00070)) ? 'x' : '-';
	mode[7] = ((m & 00004) && (m & 00007)) ? 'r' : '-';
	mode[8] = ((m & 00002) && (m & 00007)) ? 'w' : '-';
	mode[9] = ((m & 00001) && (m & 00007)) ? 'x' : '-';
	mode[3] = ((m & 04000) && mode[3] == 'x') ? 's' : mode[3];
	mode[6] = ((m & 02000) && mode[6] == 'x') ? 's' : mode[6];
	mode[9] = ((m & 01000) && mode[9] == 'x') ? 't' : mode[9];
	mode[3] = ((m & 04000) && mode[3] == '-') ? 'S' : mode[3];
	mode[6] = ((m & 02000) && mode[6] == '-') ? 'S' : mode[6];
	mode[9] = ((m & 01000) && mode[9] == '-') ? 'T' : mode[9];
	mode[10] = ' '; //переделать ACL
	return (mode);
}

static void		fill_link(t_file *file)
{
	char			*buf_l;
	int				t;

	buf_l = ft_xmalloc(file->info.st_size + 1);
	ft_bzero(buf_l, file->info.st_size + 1);
	t = readlink(file->path, buf_l, file->info.st_size + 1);
	if (t < 0 && t > file->info.st_size + 1) //проверить
	{
		perror("readlink");
		exit(1);
	}
	file->name = ft_strrejoin(file->name, " -> ");
	file->name = ft_strrejoin(file->name, buf_l);
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
	//if (file->type == 'b' || file->type == 'c')
}

void			print_files(t_stack *files, int flags)
{
	static int	columns[7];

	columns[0] = flags;
	ST_ITER(files, (void (*)(void *, void *))fill_info, &columns, flags & FLAG_R);
	ST_ITER(files, (void (*)(void *, void *))print_file, columns, flags & FLAG_R);
}

