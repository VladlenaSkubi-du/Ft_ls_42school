/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 02:00:05 by jcorwin           #+#    #+#             */
/*   Updated: 2019/06/03 16:06:51 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		fill_info(t_file *file, int *columns);
static void		fill_time(t_file *file, int *columns);
static void		fill_mode(t_file *file);
static void		get_acl(t_file *file);
static void		fill_link(t_file *file);
static void		find_length(t_file *file, int *columns);
static int		get_terminal_width(void);
static void		fill_minmaz(t_file *file);

//другой файл
static void		print_file(t_file *file, int *col)
{
	int		i;
	void	**ptr;

	i = 1;
	ptr = (void **)&file->total;
	while (++i < 10)
	{
		if (col[i])
		{
			if (i == 5)
				buf_fill(((struct passwd *)*ptr)->pw_name,
				ft_strlen(((struct passwd *)*ptr)->pw_name), col[i], 1);
			else if (i == 6)
				buf_fill(((struct group *)*ptr)->gr_name,
				ft_strlen(((struct group *)*ptr)->gr_name), col[i], 1);
			else
				buf_fill(*ptr, ft_strlen(*ptr), col[i], i == 3 ? 1 : 0);
			if (i == 5 || i == 6)
				buf_add("  ", 2);
			else
				buf_add(" ", 1);
		}
		++ptr;
	}
	buf_add(file->name, ft_strlen(file->name));
	buf_add("\n", 1);
	// printf("%3s %s %3s %s  %s  %5s %s %s\n", file->total, file->mode, file->link, file->uid->pw_name, file->gid->gr_name, file->size, file->time, file->name);
}

//вторая функция в файле
static void		fill_info(t_file *file, int *columns)
{
	columns[1] += file->info.st_blocks;
	file->total = ft_utoa_base(file->info.st_blocks, 10); //переделать под другую функцию, выводится только при s флаге
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
	fill_mode(file);
	if (file->type == 'l')
		fill_link(file);
	if (file->type == 'b' || file->type == 'c')
		fill_minmaz(file);
	find_length(file, columns);
}

//третья функция в файле
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

//четвертая функция в файле
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

//пятая функция в файле
/*
**An ACL entry specifies the access permissions on the associated object
**for an individual user or a group of users as a combination of read,
**write and search/execute permissions.
**
**Для работы с ACL нужна подключенная библиотека <sys/acl.h>. Там определены
**типы структур acl_t (например: acl_type_t, acl_flag_t), и функции для
**получения списка расширенных атрибутов файла. Функция acl_get_link_np
**возвращает поинтер типа act_t на ACL или NULL и записывает ошибки в errno:
**(EACCES, EBADF, EINVAL, ENAMETOOLONG, ENOENT, ENOMEM, EOPNOTSUPP).
**Функция acl_get_entry возвращает дескриптор значения ACL, исходя из
**отправленного entry_id (ACL_FIRST_ENTRY, ACL_NEXT_ENTRY), поинтера на ACL
**и поинтера на entry для заполнения. Если в поле entry_id поставлен
**ACL_FIRST_ENTRY, тогда в entry_p вернется дескриптор для первого
**ввода ACL (В ACL entry находится entry tag type, опциональный entry
**tag qualifier, и перечисление доступов/запретов доступа). Если entry_id
** - это ACL_NEXT_ENTRY, вернется дескриптор для следующего ввода.
*/

static void		get_acl(t_file *file)
{
	ssize_t			xattr;
	acl_t			acl;
	acl_entry_t		tmp;

	acl = NULL;
	acl = acl_get_link_np(file->path, ACL_TYPE_EXTENDED); //нельзя сделать обработку ошибок, потому что у нас нет информации, у какого файла расширенные атрибуты и если их не будет у первого файла, он сразу выйдет из проги
	if (acl && acl_get_entry(acl, ACL_FIRST_ENTRY, &tmp) == -1)
	{
		acl_free(acl);
		acl = NULL;
	}
	xattr = listxattr(file->path, NULL, 0, XATTR_NOFOLLOW);
	if (xattr > 0)
		file->mode[10] = '@';
	else if (acl != NULL)
		file->mode[10] = '+';
	else
		file->mode[10] = ' ';
}

//первая функция в файле
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

/*
**A device ID consists of two parts: a major ID, identifying the class
** of the device, and a minor ID, identifying a specific instance of a
** device in that class. A device ID is represented using the type dev_t
**that is st_rdev from struct stat.
*/

//вторая функция в файле
static void		fill_minmaz(t_file *file)
{
	int				maj;
	int				min;

	maj = major(file->info.st_rdev);
	min = minor(file->info.st_rdev);
	printf("%s = maj: %d, min: %d\n", file->name, maj, min);
}

static int		get_terminal_width(void)
{
	struct winsize	sz;

	ioctl(1, TIOCGWINSZ, &sz);
	return (sz.ws_col);
}

//третья функция в файле
static void		find_width(int len, int *columns)
{
	if (*columns)
		*columns = len > *columns ? len : *columns;
}

//четвертая функция в файле
static void		find_length(t_file *file, int *columns)
{
	int			tmp;

	find_width(ft_strlen(file->total), columns + 2);
	find_width(ft_strlen(file->mode), columns + 3);
	find_width(ft_strlen(file->link), columns + 4);
	find_width(ft_strlen(file->uid->pw_name), columns + 5);
	find_width(ft_strlen(file->gid->gr_name), columns + 6);
	columns[7] = 0;
	find_width(ft_strlen(file->size), columns + 8);
	find_width(ft_strlen(file->time), columns + 9);
	//if (file->type == 'b' || file->type == 'c')
}

static void		width_init(int *columns, int flags)
{
	int		i;

	i = 2;
	if (!flags)
		flags |= FLAG_MINUS;
	columns[0] = flags;
	if (flags & FLAG_S)
		columns[2] = 1; //количетсво блочных может быть 0;
	if (flags & (FLAG_L | FLAG_G))
	{
		while (++i < 10)
			columns[i] = 1;
		columns[3] = 11;
	}
}

//первый файл
void			print_files(t_stack *files, int flags)
{
	static int	columns[11]; //0 - флаги, 1 - общий total, 2 - индивидуальный total, 3 - доступ, 4 - ссылки,
							//5 - uid, 6 - gid, 7 - мажор для устройств, 8 - минор для устройств, 9 - размер,
							//10 - время.

	if (!columns[0])
		width_init(columns, flags);
	ST_ITER(files, (void (*)(void *, void *))fill_info, columns, flags & FLAG_R);
	//printf("total %d\n", columns[1]);
	//ST_ITER(files, (void (*)(void *, void *))print_file, columns, flags & FLAG_R);
}
