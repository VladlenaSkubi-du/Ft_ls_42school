/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 17:42:46 by sschmele          #+#    #+#             */
/*   Updated: 2019/03/16 10:06:38 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*str;
	int		i;

	str = 0;
	i = 0;
	if ((len + 1) < len)
		return (NULL);
	if (s)
	{
		if (!(str = (char*)malloc((len + 1) * sizeof(*s))))
			return (NULL);
		while (len)
		{
			str[i] = s[start + i];
			i++;
			len--;
		}
		str[i] = '\0';
	}
	return (str);
}
