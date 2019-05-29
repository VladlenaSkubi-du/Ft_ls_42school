/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out_buf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorwin <jcorwin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 16:46:07 by jcorwin           #+#    #+#             */
/*   Updated: 2019/05/29 14:10:23 by jcorwin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_printerr(char *str, size_t size)
{
	write(2, str, size);
}

void	buf_err(char *str)
{
	buf_add(NULL, 0);
	ft_printerr(str, ft_strlen(str));
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
