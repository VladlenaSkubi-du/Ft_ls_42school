/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorwin <jcorwin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 02:32:52 by jcorwin           #+#    #+#             */
/*   Updated: 2019/05/23 11:55:55 by jcorwin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		st_add(t_stack *me, void *data)
{
	void	**tmp;

	if (me->size == me->next_up)
	{
		tmp = me->data;
		me->next_up *= 2;
		me->data = ft_xmalloc(sizeof(void *) * (me->next_up + 1));
		ft_memcpy(me->data, tmp, me->size * sizeof(void *));
		free(tmp);
	}
	me->data[me->size++] = data;
}

static void		st_iter(t_stack *me, void (*f)(void *, void *),
											void *param, int reverse)
{
	size_t		i;

	if (reverse)
	{
		i = me->size;
		while (i > 0)
			f(me->data[--i], param);
	}
	else
	{
		i = 0;
		while (i < me->size)
			f(me->data[i++], param);
	}
}

static t_stack	*st_del(t_stack *me)
{
	free(me->data);
	free(me);
	return (NULL);
}

t_stack			*stack_init()
{
	t_stack		*stack;

	stack = (t_stack *)ft_xmalloc(sizeof(t_stack));
	stack->size = 0;
	stack->next_up = 10;
	stack->data = ft_xmalloc(sizeof(void *) * 11);
	stack->add = st_add;
	stack->iter = st_iter;
	stack->sort = st_sort;
	stack->del = st_del;
	return (stack);
}
