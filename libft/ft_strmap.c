/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 15:50:15 by sschmele          #+#    #+#             */
/*   Updated: 2018/12/02 16:49:43 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strmap(char const *s, char (*f)(char))
{
	char	*str;
	int		len;

	if (s == NULL || f == NULL)
		return (NULL);
	len = ft_strlen(s);
	if (!(str = (char*)malloc((len + 1) * sizeof(*s))))
		return (NULL);
	while (*s)
	{
		*str = f(*s);
		str++;
		s++;
	}
	*str = '\0';
	return (str - len);
}
