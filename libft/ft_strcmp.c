/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 12:04:33 by sschmele          #+#    #+#             */
/*   Updated: 2018/12/06 11:37:45 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strcmp(const char *s1, const char *s2)
{
	int	res;

	res = 0;
	while ((*s1 != '\0') || (*s2 != '\0'))
	{
		res = (unsigned char)*s1 - (unsigned char)*s2;
		if (res == 0)
		{
			s1++;
			s2++;
		}
		else
			break ;
	}
	return (res);
}
