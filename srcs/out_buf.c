/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out_buf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorwin <jcorwin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 16:46:07 by jcorwin           #+#    #+#             */
/*   Updated: 2019/07/07 14:02:17 by jcorwin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			buf_fill(char *str, size_t len, size_t size, int left)
{
	int				i;

	i = size - len;
	if (!str || ft_strlen(str) < len)
		return ;
	if (!left)
		while (i-- > 0)
			buf_add(" ", 1);
	buf_add(str, len);
	if (left)
		while (i-- > 0)
			buf_add(" ", 1);
}

void			buf_add(char *str, size_t size)
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

static void		buf_col_del(t_buf *buf)
{
	int				i;

	i = -1;
	while (++i < buf->lines)
	{
		buf_add(buf->arr[i], buf->t_width);
		buf_add("\n", 1);
		free(buf->arr[i]);
	}
	free(buf->arr);
	buf->arr = NULL;
}

static void		buf_col_init(t_file *file, int col[4], t_buf *buf)
{
	buf->i = 0;
	buf->size = col[1];
	buf->s_width = col[3];
	col[2] = (col[2] <= buf->s_width) ? buf->s_width : col[2];
	if (file->color[1])
	{
		buf->t_width = ((int)(col[2] / buf->s_width)) * (buf->s_width + 15);
		buf->s_width += 15;
	}
	else
		buf->t_width = ((int)(col[2] / buf->s_width)) * (buf->s_width);
	buf->t_width += col[0] + 1;
	buf->lines = (int)(buf->t_width / buf->s_width);
	buf->lines = (int)(buf->size / buf->lines +
								(buf->size % buf->lines ? 1 : 0));
	buf->arr = ft_xmalloc(sizeof(char *) * buf->lines);
	while (buf->i < buf->lines)
		buf->arr[buf->i++] = ft_xmalloc(buf->t_width);
	buf->i = 0;
}

void			buf_col(t_file *file, int col[4])
{
	static t_buf	buf;
	int				len;
	char			*str;

	if (!buf.arr)
		buf_col_init(file, col, &buf);
	str = (file->color[1]) ?
			ft_strjoin(file->color, file->name) : ft_strdup(file->name);
	len = ft_strlen(str);
	if (buf.i <= buf.lines && col[0])
		ft_memset(buf.arr[buf.i % buf.lines] +
			(buf.i / buf.lines * buf.s_width), ' ', col[0] + 1);
	else
		ft_memset(buf.arr[buf.i % buf.lines] +
			(buf.i / buf.lines * buf.s_width), ' ', col[0]);
	ft_memcpy(buf.arr[buf.i % buf.lines] + (buf.i / buf.lines * buf.s_width)
		+ col[0] - ft_strlen(file->total), file->total, ft_strlen(file->total));
	ft_memcpy(buf.arr[buf.i % buf.lines] + (buf.i / buf.lines * buf.s_width) +
						col[0] + 1, str, ft_strlen(str));
	ft_memset(buf.arr[buf.i % buf.lines] + (buf.i / buf.lines * buf.s_width) +
						col[0] + 1 + len, ' ', buf.s_width - len);
	free(str);
	if (buf.i++ == col[1] - 1)
		buf_col_del(&buf);
}
