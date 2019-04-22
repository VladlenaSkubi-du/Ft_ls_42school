/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 14:18:52 by sschmele          #+#    #+#             */
/*   Updated: 2018/11/30 16:41:59 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strtrim(char const *s)
{
	int		i;
	int		a;
	int		len;
	char	*str;

	i = 0;
	len = 0;
	str = 0;
	if (!s)
		return (NULL);
	while (*s == ' ' || *s == '\n' || *s == '\t')
		s++;
	a = i;
	while (s[i])
		i++;
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t' || s[i] == '\0')
		i--;
	while (a++ <= i)
		len++;
	if (!(str = (char*)malloc((len + 1) * sizeof(s[i]))))
		return (NULL);
	ft_strncpy(str, s, len);
	str[len] = '\0';
	return (str);
}
