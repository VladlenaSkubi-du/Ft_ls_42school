/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorwin <jcorwin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 12:48:32 by jcorwin           #+#    #+#             */
/*   Updated: 2019/05/19 11:22:55 by jcorwin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	file_strcmp(t_file *left, t_file *right)
{
	return (ft_strcmp(left->name, right->name));
}

static int	file_sizecmp(t_file *left, t_file *right)
{
	return (left->info.st_size - right->info.st_size);
}

static int	file_timecmp(t_file *left, t_file *right)
{
	return(left->info.st_mtime - right->info.st_mtime);
}

static int	file_atimecmp(t_file *left, t_file *right)
{
	return(left->info.st_atime - right->info.st_atime);
}

void		*files_sort(int flags)
{
	int (*f)(t_file *left, t_file *right);

	if (flags & FLAG_F)
		return (NULL);
	if (flags & FLAG_SS)
		f = file_sizecmp;
	else if (flags & FLAG_T)
		f = file_timecmp;
	else if (flags & FLAG_U)
		f = file_atimecmp;
	else
		f = file_strcmp;
	return (f);
}
