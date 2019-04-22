/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchrnew.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 11:47:34 by sschmele          #+#    #+#             */
/*   Updated: 2018/12/14 13:39:17 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*not(void)
{
	char		*new;

	new = ft_memalloc(1);
	if (new == NULL)
		return (NULL);
	return (new);
}

char			*ft_strchrnew(char *s, int c)
{
	int		i;
	char	*p;
	char	*new;
	int		flag;

	i = 0;
	p = (char*)s;
	flag = 0;
	while (s[i++])
		if (s[i] == (unsigned char)c)
		{
			flag = 1;
			p = p + i;
			break ;
		}
	p++;
	if ((*s == '\0') || (c == '\0') || flag == 0)
		return (not());
	else
	{
		if (!(new = ft_strdup(p)))
			return (NULL);
	}
	return (new);
}
