/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorwin <jcorwin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 13:32:14 by jcorwin           #+#    #+#             */
/*   Updated: 2019/05/14 16:03:10 by jcorwin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_file			*file_new(t_file *start)
{
	t_file	*new;

	new = (t_file *)ft_xmalloc(sizeof(t_file));
	if (!start)
	{
		new->next = new;
		new->prev = new;
		return(new);
	}
	start->prev->next = new;
	new->prev = start->prev;
	new->next = start;
	start->prev = new;
	return (start);
}

t_file			*file_cut(t_file *start, t_file *node)
{
	if (start == start->next)
		return (NULL);
	if (node == start)
		start = start->next;
	if (node)
	{
		node->prev->next = node->next;
		node->next->prev = node->prev;
	}
	return (start);
}

void			file_insert(t_file *prev, t_file *node)
{
	prev->next->prev = node;
	node->next = prev->next;
	prev->next = node;
	node->prev = prev;
}

t_file			*file_slip(t_file *start, int (*f)(t_file *left, t_file *right))
{
	while (f(start->prev, start) < 0)
		start = start->prev;
	return (start);
}

t_file			*file_swap(t_file *start, t_file *left, t_file *right)
{
	t_file	*prev1;
	t_file	*prev2;
	int		tmp;

	tmp = left->fromstart;
	left->fromstart = right->fromstart;
	right->fromstart = tmp;
	prev1 = left->prev;
	prev2 = right->prev;
	if (prev2 == left)
		prev2 = right;
	start = file_cut(start, left);
	start = file_cut(start, right);
	file_insert(prev1, right);
	file_insert(prev2, left);
	return (start);
}

t_file			*file_del(t_file *start)
{
	t_file	*cur;
	t_file	*prev;

	if (!start)
		return (NULL);
	cur = start->next;
	while (cur != start)
	{
		prev = cur;
		cur = cur->next;
		free(prev);
	}
	free(start);
	return (NULL);
}

void			file_count(t_file *start)
{
	t_file	*cur;
	int		i;

	if (!start)
		return ;
	// start->tostart = 0;
	start->fromstart = 0;
	i = 0;
	cur = start->next;
	while (cur != start)
	{
		cur->fromstart = ++i;
		cur = cur->next;
	}
	// i = 0;
	// cur = start->prev;
	// while (cur != start)
	// {
	// 	cur->tostart = ++i;
	// 	cur = cur->prev;
	// }
}

void			file_foreach(t_file *start, void (*f)(t_file *cur))
{
	t_file	*cur;

	f(start);
	cur = start->next;
	while (cur != start)
	{
		f(cur);
		cur = cur->next;
	}
}
