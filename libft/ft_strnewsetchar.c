/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnewsetchar.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 09:41:22 by sschmele          #+#    #+#             */
/*   Updated: 2019/03/16 09:50:01 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				*ft_strnewsetchar(size_t size, char c)
{
	char			*s;
	size_t			i;

	if ((size + 1) < size)
		return (NULL);
	i = -1;
	if (!(s = malloc(size + 1)))
		return (NULL);
	while (++i < size)
		s[i] = (unsigned char)c;
	s[size] = '\0';
	return (s);
}
