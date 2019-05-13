/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_chr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorwin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 18:00:26 by jcorwin           #+#    #+#             */
/*   Updated: 2019/04/24 09:11:03 by jcorwin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "libft.h"

size_t			ft_strlen(const char *s)
{
	size_t			*iter;
	unsigned char	*end;

	end = (unsigned char *)s;
	while ((size_t)end % sizeof(size_t))
		if (!(*end++))
			return (end - (unsigned char *)s - 1);
	iter = (size_t *)end;
	while ((*iter - 0x0101010101010101 & ~(*iter) & 0x8080808080808080) == 0)
		iter++;
	end = (unsigned char *)iter;
	while (*end)
		++end;
	return (end - (unsigned char *)s);
}
