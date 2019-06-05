/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 19:08:49 by sschmele          #+#    #+#             */
/*   Updated: 2019/06/05 19:11:25 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	*ft_xmalloc(size_t size)
{
	void	*ptr;

	if (!(ptr = malloc(size)))
	{
		write(2, "No space left\n", 15);
		exit(1);
	}
	ft_bzero(ptr, size);
	return (ptr);
}

void		ft_stradd_nb(char *s, long nb)
{
	int		i;
	int		a;
	char	*main;

	i = -1;
	a = 1;
	main = "0123456789ABCDEF";
	if (nb == 0)
		s[0] = 0 + '0';
	else
	{
		if (nb < 0)
		{
			s[++i] = '-';
			nb *= -1;
		}
		while (a <= nb / 10)
			a *= 10;
		while (nb)
		{
			s[++i] = main[(nb / a) % 10];
			nb %= a;
			a /= 10;
		}
	}
}