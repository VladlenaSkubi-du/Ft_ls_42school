/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_stackfiles_info_2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 19:26:28 by sschmele          #+#    #+#             */
/*   Updated: 2019/06/18 19:08:51 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void			get_acl(t_file *file)
{
	ssize_t			xattr;
	acl_t			acl;
	acl_entry_t		tmp;

	acl = NULL;
	acl = acl_get_link_np(file->path, ACL_TYPE_EXTENDED);
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

void		fill_mode(t_file *file)
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

void		fill_time(t_file *file, int *columns)
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

/*
**A device ID consists of two parts: a major ID, identifying the class
** of the device, and a minor ID, identifying a specific instance of a
** device in that class. A device ID is represented using the type dev_t
**that is st_rdev from struct stat.
*/

void			fill_minmaz(t_file *file) // костыль на костыле
{
	int 			i;
	char			*maj;
	char			*min;

	maj = ft_utoa_base(major(file->info.st_rdev), 10);
	min = ft_utoa_base(minor(file->info.st_rdev), 10);
	file->size = ft_strjoin(" ", maj);
	file->size = ft_strrejoin(file->size, ",");
	i = 4 - ft_strlen(min);
	while (i-- > 0)
		file->size = ft_strrejoin(file->size, " ");
	file->size = ft_strrejoin(file->size, min);
	free(maj);
	free(min);
}

void			change_name(t_file *file, int flags)
{
	char			*buf_l;
 	int				t;

	if (file->type == 'd' && (flags & (FLAG_P | FLAG_FF)))
		file->name = ft_strrejoin(file->name, "/");
	if (file->type == 'l' && (flags & FLAG_FF))
		file->name = ft_strrejoin(file->name, "@");
	if (file->type == '-' && (flags & FLAG_FF))
		if (file->mode[3] == 'x' || file->mode[3] == 's' ||
		file->mode[6] == 'x' || file->mode[6] == 's' || file->mode[9] == 'x')
			file->name = ft_strrejoin(file->name, "*");
	if (file->type == 'l' && (flags & (FLAG_L | FLAG_G)))
	{
		buf_l = ft_xmalloc(file->info.st_size + 1);
		ft_bzero(buf_l, file->info.st_size + 1);
		t = readlink(file->path, buf_l, file->info.st_size + 10);
		if (t < 0 && t > file->info.st_size + 1)
		{
			perror("readlink");
			exit(1);
		}
		file->name = ft_strrejoin(file->name, " -> ");
		file->name = ft_strrejoin(file->name, buf_l);
		free(buf_l);
	}
}