/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorwin <jcorwin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 12:48:32 by jcorwin           #+#    #+#             */
/*   Updated: 2019/05/14 22:32:03 by jcorwin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	file_strcmp(t_file *left, t_file *right)
{
	return (ft_strcmp(left->name, right->name));
}

static int	file_sizecmp(t_file *left, t_file *right)
{
	return (left->buf.st_size - right->buf.st_size);
}

static int	file_timecmp(t_file *left, t_file *right)
{
	return(left->buf.st_mtime - right->buf.st_mtime);
}

static int	file_atimecmp(t_file *left, t_file *right)
{
	return(left->buf.st_atime - right->buf.st_atime);
}

t_file	*files_sort(t_file *start, int flags)
{
	int (*f)(t_file *left, t_file *right);

	if (flags & FLAG_F)
		return ;
	if (start->prev->fromstart > 2)
	{
		if (flags & FLAG_SS)
			f = file_sizecmp;
		else if (flags & FLAG_T)
			f = file_timecmp;
		else if (flags & FLAG_U)
			f = file_atimecmp;
		else
			f = file_strcmp;
		if (flags & FLAG_R)
			quick_sort_list(start, start->prev, start, f);
		else
			quick_sort_list(start, start, start->prev, f);
	}
	if (flags & FLAG_R)
		while (f(start, start->prev) < 0)
			start = start->prev;
	else
		while (f(start->prev, start) < 0)
			start = start->prev;
	return start;
}