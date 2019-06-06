/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_by_flags.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 12:48:32 by jcorwin           #+#    #+#             */
/*   Updated: 2019/06/06 16:50:01 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	file_strcmp(t_file *left, t_file *right)
{
	return (ft_strcmp(left->name, right->name));
}

static int	file_sizecmp(t_file *left, t_file *right)
{
	if (right->info.st_size == left->info.st_size)
		return (file_strcmp(left, right));
	return (right->info.st_size - left->info.st_size);
}

static int	file_timecmp(t_file *left, t_file *right)
{
	if (right->info.st_mtime == left->info.st_mtime)
		return (file_strcmp(left, right));
	return (right->info.st_mtime - left->info.st_mtime);
}

static int	file_atimecmp(t_file *left, t_file *right)
{
	if (right->info.st_atime == left->info.st_atime)
		return (file_strcmp(left, right));
	return (right->info.st_atime - left->info.st_atime);
}

// static int	file_ctimecmp(t_file *left, t_file *right)
// {
// 	if (right->info.st_ctime == left->info.st_ctime)
// 		return (file_strcmp(left, right));
// 	return (right->info.st_ctime - left->info.st_ctime);
// }

//вынести в parser.c
void		*files_sort(int flags)
{
	int (*f)(t_file *left, t_file *right);

	if (flags & FLAG_F)
		return (NULL);
	if (flags & FLAG_SS)
		f = file_sizecmp;
	else if (flags & FLAG_U && flags & FLAG_T)
		f = file_atimecmp;
	//else if (flags & FLAG_C && flags & FLAG_T)
	//	f = file_ctimecmp;
	else if (flags & FLAG_T)
		f = file_timecmp;
	else
		f = file_strcmp;
	return (f);
}
