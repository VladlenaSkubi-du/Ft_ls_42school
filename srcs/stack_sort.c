/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorwin <jcorwin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 04:52:12 by jcorwin           #+#    #+#             */
/*   Updated: 2019/05/21 17:25:58 by jcorwin          ###   ########.fr       */
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
	if (left->num < i->num - 1)
		quick_sort_plist(start, left, i->prev, f);
	if (i->next->num < right->num)
		quick_sort_plist(start, i->next, right, f);
}

static void merge_sort(void *base, size_t nel, size_t width, int (*cmp)(const void *, const void *))
{
    char   *left;
    char   *right;
    size_t  ls;
    size_t  rs;
    size_t  mid;
    size_t  i;
    size_t  j;
    size_t  k;

    /* Find the mid and deal with an odd number of elements. */
    mid = nel/2;
    ls  = mid;
    rs  = mid;

    if (nel > 2 && nel % 2 != 0)
        ls++;

    /* Copy the elements into tmp arrays. */
    left  = malloc(ls*width);
    right = malloc(rs*width);
    memcpy(left, base, ls*width);
    memcpy(right, base+(ls*width), rs*width);

    merge_sort(left, ls, width, cmp);
    merge_sort(right, rs, width, cmp);

    i = 0;
    j = 0;
    k = 0;
    /* Merge the tmp arrays back into the base array in
     * sorted order. */
    while (i < ls && j < rs) {
        if (cmp(left+(i*width), right+(j*width)) <= 0) {
            memcpy(base+(k*width), left+(i*width), width);
            i++;
        } else {
            memcpy(base+(k*width), right+(j*width), width);
            j++;
        }
        k++;
    }

    /* If left is longer than right copy the remaining elements
     * over */
    while (i < ls) {
        memcpy(base+(k*width), left+(i*width), width);
        i++;
        k++;
    }

    /* If right is longer than right copy the remaining elements
     * over */
    while (j < rs) {
        memcpy(base+(k*width), right+(j*width), width);
        j++;
        k++;
    }

    free(right);
    free(left);
}

void			st_sort(t_stack *me, int (*f)(void *, void *))
{
	if (f)
	{
		if (me->counter > 1)
			quick_sort_plist(me->list, me->list, me->list->prev, f);
	}
}
