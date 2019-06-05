/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_stackfiles_info_2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorwin <jcorwin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 19:26:28 by sschmele          #+#    #+#             */
/*   Updated: 2019/06/05 21:00:35 by jcorwin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			fill_link(t_file *file)
{
	char			*buf_l;
	int				t;

	buf_l = ft_xmalloc(file->info.st_size + 1);
	ft_bzero(buf_l, file->info.st_size + 1);
	t = readlink(file->path, buf_l, file->info.st_size + 1);
	if (t < 0 && t > file->info.st_size + 1)
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

void			fill_minmaz(t_file *file)
{
	if (file->type == 'c' || file->type == 'b')
	{
		file->maj = ft_strdup(" ");
		file->maj = ft_strrejoin(file->maj,
				ft_utoa_base(major(file->info.st_rdev), 10));
		file->maj = ft_strrejoin(file->maj, ",");
		file->min = ft_utoa_base(minor(file->info.st_rdev), 10);
	}
	else
	{
		file->min = ft_strdup("0");
	}
}

static void		find_width(int len, int *columns)
{
	if (*columns)
		*columns = len > *columns ? len : *columns;
}

void			find_length(t_file *file, int *columns)
{
	int				tmp;

	find_width(ft_strlen(file->total), columns + 2);
	find_width(ft_strlen(file->mode), columns + 3);
	find_width(ft_strlen(file->link), columns + 4);
	find_width(ft_strlen(file->uid->pw_name), columns + 5);
	find_width(ft_strlen(file->gid->gr_name), columns + 6);
	find_width(ft_strlen(file->size), columns + 9);
	find_width(ft_strlen(file->maj), columns + 7);
	find_width(ft_strlen(file->min), columns + 8);
}

void			get_acl(t_file *file)
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
