/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorwin <jcorwin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 04:52:12 by jcorwin           #+#    #+#             */
/*   Updated: 2019/05/15 15:13:32 by jcorwin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		quick_sort_plist(t_plist *start, t_plist *left, t_plist *right,
									int (*f)(void *left, void *right))
{
	t_plist	*p;
	t_plist	*i;
	t_plist	*j;
	void	*tmp;

	i = left;
	j = right;
	while (i != j)
	{
		if (f(i->data, j->data) > 0 == (i->num < j->num))
		{
			tmp = i->data;
			i->data = j->data;
			j->data = tmp;
			p = i;
			i = j;
			j = (p->num < j->num) ? p->next : p->prev;
		}
		else
			j = (i->num < j->num) ? j->prev : j->next;
	}
	if (left->num < i->num - 1)
		quick_sort_plist(start, left, i->prev, f);
	if (i->next->num < right->num)
		quick_sort_plist(start, i->next, right, f);
}

void			st_sort(t_stack *me, int (*f)(void *, void *))
{
	if (f)
	{
		if (me->counter > 1)
			quick_sort_plist(me->list, me->list, me->list->prev, f);
	}
}
