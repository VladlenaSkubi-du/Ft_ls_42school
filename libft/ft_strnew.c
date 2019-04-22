/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 14:11:10 by sschmele          #+#    #+#             */
/*   Updated: 2019/04/04 20:09:59 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strnew(size_t size)
{
	char	*p;
	size_t	i;

	if ((size + 1) < size)
		return (NULL);
	i = -1;
	if (!(p = malloc(size + 1)))
		return (NULL);
	while (++i <= size)
		p[i] = '\0';
	return (p);
}
