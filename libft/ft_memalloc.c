/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 12:51:29 by sschmele          #+#    #+#             */
/*   Updated: 2019/03/16 10:35:49 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				*ft_memalloc(size_t size)
{
	unsigned char	*str;
	void			*p;
	size_t			i;

	if (!(p = (void*)malloc(size)))
		return (NULL);
	i = -1;
	str = p;
	while (++i < size)
		str[i] = '\0';
	return (p);
}
