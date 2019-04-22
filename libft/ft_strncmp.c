/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 17:21:58 by sschmele          #+#    #+#             */
/*   Updated: 2018/12/06 11:38:50 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	int		res;

	i = 0;
	res = 0;
	while ((n > 0) && (s1[i] != '\0' || s2[i] != '\0'))
	{
		res = (unsigned char)s1[i] - (unsigned char)s2[i];
		n--;
		if (res == 0)
			i++;
		else
			break ;
	}
	return (res);
}
