/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out_buf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 16:46:07 by jcorwin           #+#    #+#             */
/*   Updated: 2019/06/06 18:36:48 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	buf_err(char *str)
{
	buf_add(NULL, 0);
	ft_printerr(str, ft_strlen(str));
}

void	buf_add_num(unsigned int n)
{
	int		a;
	long	res;
	char	ch[1];

	a = 1;
	res = n;
	if (res < 0)
	{
		res *= -1;
		ft_putchar('-');
	}
	while (a <= res / 10)
		a *= 10;
	while (a != 0)
	{
		*ch = res / a + '0';
		buf_add(ch, 1);
		res = res % a;
		a = a / 10;
	}
}

void	buf_fill(char *str, size_t len, size_t size, int left)
{
	int		i;

	i = size - len;
	if (!left)
		while (i-- > 0)
			buf_add(" ", 1);
	buf_add(str, len);
	if (left)
		while (i-- > 0)
			buf_add(" ", 1);
}

void	buf_add(char *str, size_t size)
{
	static char		buf[OUT_BUF];
	static char		*ptr = buf;

	//функция вывода по флагам - С - дефолтный с выравниванием, 1 - столбик, p - со слешами, F - со слешами, @ или *, G - с цветами
	if (!str && !size)
	{
		write(1, buf, ptr - buf);
		ptr = buf;
	}
	else if (size + (size_t)(ptr - buf) < OUT_BUF)
	{
		ft_memcpy(ptr, str, size);
		ptr += size;
	}
	else
	{
		write(1, buf, ptr - buf);
		write(1, str, size);
		ptr = buf;
	}
}
