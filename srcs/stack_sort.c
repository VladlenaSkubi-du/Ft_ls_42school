/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorwin <jcorwin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 04:52:12 by jcorwin           #+#    #+#             */
/*   Updated: 2019/05/23 13:02:20 by jcorwin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		quick_sort(void **arr, size_t left, size_t right,
									int (*f)(void *left, void *right))
{
	size_t		p;
	size_t		i;
	size_t		j;
	void		*tmp;

	i = left;
	j = right;
	while (i != j)
		if (f(arr[i], arr[j]) > 0 == (i < j))
		{
			tmp = arr[i];
			arr[i] = arr[j];
			arr[j] = tmp;
			p = i;
			i = j;
			j = (p < j) ? p + 1 : p - 1;
		}
		else
			j = (i < j) ? j - 1 : j + 1;
	if (left != i && left < i - 1)
		quick_sort(arr, left, i - 1, f);
	if (i + 1 < right)
		quick_sort(arr, i + 1, right, f);
}

void			st_sort(t_stack *me, int (*f)(void *, void *))
{
	if (f)
	{
		if (me->size > 1)
			quick_sort(me->data, 0, me->size - 1, f);
	}
}
