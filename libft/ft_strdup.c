/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 14:49:53 by sschmele          #+#    #+#             */
/*   Updated: 2018/12/06 11:20:56 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		len;
	char	*temp;

	len = ft_strlen(s1);
	if (!(temp = (char*)malloc((len + 1) * sizeof(*s1))))
	{
		free(temp);
		return (NULL);
	}
	while (*s1 != '\0')
	{
		*temp = *s1;
		temp++;
		s1++;
	}
	*temp = '\0';
	return (temp -= len);
}
