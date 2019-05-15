/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorwin <jcorwin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 02:32:52 by jcorwin           #+#    #+#             */
/*   Updated: 2019/05/15 16:13:29 by jcorwin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		st_add(t_stack *me, void *data)
{
	t_plist		*ptr;

	if (!data)
		return ;
	ptr = (t_plist *)ft_xmalloc(sizeof(t_plist));
	ptr->data = data;
	if (me->list == NULL)
	{
		ptr->num = 1;
		ptr->next = ptr;
		ptr->prev = ptr;
		me->list = ptr;
	}
	else
	{
		me->list->prev->next = ptr;
		ptr->prev = me->list->prev;
		me->list->prev = ptr;
		ptr->next = me->list;
		ptr->num = ptr->prev->num + 1;
	}
	me->counter++;
}

static void		st_iter(t_stack *me, void (*f)(void *, void *), void *param)
{
	t_plist		*cur;

	if (!me || !me->list || !f)
		return ;
	cur = me->list->next;
	f(me->list->data, param);
	while (cur != me->list)
	{
		f(cur->data, param);
		cur = cur->next;
	}
}

static void		st_iterr(t_stack *me, void (*f)(void *, void *), void *param)
{
	t_plist		*cur;

	if (!me || !me->list || !f)
		return ;
	cur = me->list->prev;
	while (cur != me->list)
	{
		f(cur->data, param);
		cur = cur->prev;
	}
	f(cur->data, param);
}

static void		st_del(t_stack *me)
{
	t_plist		*cur;
	t_plist		*prev;

	prev = me->list;
	while (cur != me->list)
	{
		cur = prev->next;
		free(prev);
		prev = cur;
	}
}

t_stack			*stack_init()
{
	t_stack		*stack;

	stack = (t_stack *)ft_xmalloc(sizeof(t_stack));
	stack->list = NULL;
	stack->counter = 0;
	stack->add = st_add;
	stack->iter = st_iter;
	stack->iterr = st_iterr;
	stack->sort = st_sort;
	stack->del = st_del;
	return (stack);
}
