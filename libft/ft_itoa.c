/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 11:13:56 by sschmele          #+#    #+#             */
/*   Updated: 2018/12/22 19:40:06 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_itoa_2(long res, char *str, int a, int n)
{
	int		i;

	i = 0;
	if (n < 0)
	{
		str[i] = '-';
		i++;
	}
	while (a != 0)
	{
		str[i] = res / a + '0';
		res %= a;
		a /= 10;
		i++;
	}
	return (str);
}

char		*ft_itoa(int n)
{
	char	*str;
	long	res;
	int		a;
	int		len;

	res = n;
	a = 1;
	len = 0;
	if (res < 0)
	{
		res *= -1;
		len++;
	}
	while (a <= res / 10)
	{
		a *= 10;
		len++;
	}
	if (!(str = ft_strnew(len + 1)))
		return (NULL);
	return (ft_itoa_2(res, str, a, n));
}
