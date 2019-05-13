/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorwin <jcorwin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 12:48:32 by jcorwin           #+#    #+#             */
/*   Updated: 2019/05/13 16:36:20 by jcorwin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		file_strcmp(t_file *left, t_file *right)
{
	return (ft_strcmp(left->name, right->name));
}

void	quickSort(t_file *start, t_file *left, t_file *right,
									int (*f)(t_file *left, t_file *right))
{
	t_file	*p;
	t_file	*i;
	t_file	*j;

	i = left;
	j = right;
	while (i != j)
	{
		if(f(i, j) > 0 == (i->fromstart < j->fromstart))
		{
			start = file_swap(start, i, j);
			p = i;
			i = j;
			j = p->fromstart < j->fromstart ? p->next : p->prev;
		}
		else
			j = i->fromstart < j->fromstart ? j->prev : j->next;
	}
	if (left->fromstart < i->fromstart - 1)
		quickSort(start, left, i->prev, f);
	if (i->next->fromstart < right->fromstart)
		quickSort(start, i->next, right, f);
}

// void	quickSort(t_file *start, t_file *left, t_file *right,
// 									int (*f)(t_file *left, t_file *right))
// {
// 	t_file *i;
// 	t_file *j;

// 	i = left;
// 	j = left;
// 	while (i != right)
// 	{
// 		while (j != right->prev)
// 		{
// 			if (f(i, j) > 0)
// 				start = file_swap(start, i, j);
// 			j = j->next;
// 		}
// 		j = left;
// 		i = i->next;
// 	}
// }
