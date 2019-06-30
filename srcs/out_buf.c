/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out_buf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorwin <jcorwin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 16:46:07 by jcorwin           #+#    #+#             */
/*   Updated: 2019/06/30 21:28:53 by jcorwin          ###   ########.fr       */
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

static char		**buf_col_del(char **arr, int lines, int t_width)
{
	int		i;
	
	i = -1;
	while (++i < lines)
	{
		buf_add(arr[i], t_width);
		buf_add("\n", 1);
	}
	free(arr);
	return (NULL);
}

// static void		buf_col_fill(t_file *file, int size, int t_width, int s_width)
// {
// 	static char		**arr;
// 	static int		i;
// 	static int		lines;

// 	ft_memcpy(arr[i % lines] + (i / lines * s_width), file->name, s_width);
// 	ft_memset(arr[i % lines] + (i / lines * s_width) + ft_strlen(file->name), ' ', s_width - ft_strlen(file->name));
// }

// static int		buf_col_init(int col[3], char ***arr, int *lines, int *t_width)
// {
// 	int		size;
// 	int		s_width;
// 	int		i;

// 	size = col[0];
// 	s_width = col[2];
// 	*t_width = ((int)(col[1] / s_width)) * s_width;
// 	*lines = (int)(*t_width / s_width);
// 	*lines = (int) (size / *lines + (size % *lines ? 1 : 0));
// 	arr = ft_xmalloc(sizeof(char *) * *lines);
// 	i = 0;
	// while (i < *lines)
	// 	arr[i++] = ft_xmalloc(*t_width);
// 	return (0);
// }

// void			buf_col(t_file *file, int col[3])
// {
// 	static char		**arr;
// 	static int		lines;
// 	static int		i;
// 	static int		t_width;
// 	static int		s_width;
	
// 	if (!arr)
// 		i = buf_col_init(col, &arr, &lines, &t_width);
// 	else
// 	{
// 		ft_memcpy(arr[i % lines] + (i / lines * col[2]), file->name, s_width);
// 	}
// 	buf_col_fill(file, arr, lines, i);
	// if (++i == col[0])
	// 	arr = buf_col_del(arr, lines, t_width);
// }

void			buf_col(t_file *file, int col[4])
{
	static char		**arr;
	static int		lines;
	static int		i;
	static int		size;
	static int		t_width;
	static int		s_width;
	int				len;
	char			*str;

	if (!arr)
	{
		i = 0;
		size = col[1];
		s_width = col[3];
		// printf("%d\n", s_width);
		if (file->color[1])
		{
			// t_width = ((int)(col[1] / s_width)) * (s_width + 12);
			// s_width += 12;
			t_width = ((int)(col[2] / s_width)) * (s_width + 15);
			s_width += 15;
		}
		else
			t_width = ((int)(col[2] / s_width)) * (s_width);
		lines = (int)(t_width / s_width);
		lines = (int)(size / lines + (size % lines ? 1 : 0));
		arr = ft_xmalloc(sizeof(char *) * lines);
		while (i < lines)
			arr[i++] = ft_xmalloc(t_width);
		i = 0;
	}
	//len = ft_strlen(file->name) - (file->color[1] ? 4 : 0);
	// len = ft_strlen(file->name) - (ft_strlen(file->color) ? ft_strlen(file->color) + 4 : 0);
	str = ft_strjoin(file->color, file->name);
	len = ft_strlen(str);
	//printf("max = %d	%s  -  %d\n", s_width, str, ft_strlen(str));
	ft_memcpy(arr[i % lines] + (i / lines * s_width), str, ft_strlen(str));
	ft_memset(arr[i % lines] + (i / lines * s_width) + len, ' ', s_width - len);
	// ft_memset(arr[i % lines] + (i / lines * s_width), ' ', col[0] - ft_strlen(file->total));
	// ft_memcpy(arr[i % lines] + (i / lines * s_width) + col[0] - ft_strlen(file->total), file->total, ft_strlen(file->total));
	// ft_memcpy(arr[i % lines] + (i / lines * s_width) + ft_strlen(file->total) + 1, str, ft_strlen(str));
	// ft_memset(arr[i % lines] + (i / lines * s_width) + ft_strlen(file->total) + 1 + len, ' ', s_width - len);
	if (i++ == col[1] - 1)
		arr = buf_col_del(arr, lines, t_width);
	free(str);
}