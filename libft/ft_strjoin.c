/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 19:06:52 by sschmele          #+#    #+#             */
/*   Updated: 2018/12/02 19:18:52 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		len_1;
	int		len_2;

	str = 0;
	if (s1 && s2)
	{
		len_1 = ft_strlen(s1);
		len_2 = ft_strlen(s2);
		if (!(str = ft_memalloc(len_1 + len_2 + 1)))
			return (NULL);
		ft_strcat(str, s1);
		ft_strcat(str, s2);
	}
	return (str);
}
