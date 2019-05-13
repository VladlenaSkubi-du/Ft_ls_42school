/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchri.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorwin <jcorwin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 17:19:41 by jcorwin           #+#    #+#             */
/*   Updated: 2019/05/13 19:42:46 by jcorwin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned		ft_strchr(const char *s, int c)
{
	size_t			*iter;
	unsigned char	*end;
	size_t			mask;
	int				i;

	mask = 0;
	i = -1;
	while (++i < (int)sizeof(size_t))
		mask |= ((size_t)(1 + (size_t)c) << ((size_t)i * 8));
	end = (unsigned char *)s;
	while ((size_t)end % sizeof(size_t))
	{
		if (*end == (unsigned char)c || *end == '\0')
			return (*end == (unsigned char)c ? (char *)end : NULL);
		++end;
	}
	iter = (size_t *)end;
	while ((*iter - mask & ~(*iter) & 0x8080808080808080) == 0 &&
			(*iter - 0x0101010101010101 & ~(*iter) & 0x8080808080808080) == 0)
		iter++;
	end = (unsigned char *)iter;
	while (*end && *end != (unsigned char)c)
		++end;
	return (*end == (unsigned char)c ? (unsigned)(s - (char *)end) : -1);
}
