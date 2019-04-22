/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchrlen.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 12:00:36 by sschmele          #+#    #+#             */
/*   Updated: 2019/01/10 16:29:13 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strchrlen(const char *s, int c)
{
	int		i;
	size_t	res;

	i = -1;
	res = 0;
	while (s[++i] != '\0')
	{
		if (s[i] == (unsigned char)c)
			return (res);
		res++;
	}
	return (res);
}
