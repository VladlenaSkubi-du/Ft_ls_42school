/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 18:32:09 by sschmele          #+#    #+#             */
/*   Updated: 2019/03/16 10:07:48 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strndup(const char *s1, size_t n)
{
	char	*temp;
	int		i;

	i = 0;
	if ((n + 1) < n)
		return (NULL);
	if (!(temp = (char*)malloc((n + 1) * sizeof(*s1))))
		return (NULL);
	while (n)
	{
		temp[i] = s1[i];
		i++;
		n--;
	}
	temp[i] = '\0';
	return (temp);
}
