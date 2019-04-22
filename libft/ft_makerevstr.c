/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putrevstr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 11:27:59 by sschmele          #+#    #+#             */
/*   Updated: 2018/12/03 12:21:10 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_makerevstr(char *s)
{
	char	*str;
	int		i;
	int		len;

	str = 0;
	if (s && *s != '\0')
	{
		i = 0;
		len = ft_strlen(s);
		if (!(str = (char*)malloc(len * sizeof(char))))
			return (0);
		while (len--)
		{
			str[i] = s[len];
			i++;
		}
		str[i] = '\0';
	}
	return (str);
}
