/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_stackfile.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorwin <jcorwin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 02:00:05 by jcorwin           #+#    #+#             */
/*   Updated: 2019/06/30 19:44:20 by jcorwin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

// Проблемы:
											// at-e4% ./ft_ls -dl ./README.md ../7_Ft_printf_with_Petr /dev/rdisk0

// drwxr-xr-x  16 sschmele  2018          544 Apr 27 16:15 ../7_Ft_printf_with_Petr
// -rw-r--r--   1 sschmele  2018        10698 Jun  7 11:33 ./README.md
// crw-r-----   1 root      operator   1,   0 Jun 15 16:49 /dev/rdisk0

											// at-e4% ls -dl ./README.md ../7_Ft_printf_with_Petr /dev/rdisk0

// drwxr-xr-x  16 sschmele  2018           544 Apr 27 16:15 ../7_Ft_printf_with_Pet
// r
// -rw-r--r--   1 sschmele  2018         10698 Jun  7 11:33 ./README.md
// crw-r-----   1 root      operator    1,   0 Jun 15 16:49 /dev/rdisk0

											// at-e4% ls -dl ./README.md ../7_Ft_printf_with_Petr /dev/xcpm

// drwxr-xr-x  16 sschmele  2018                544 Apr 27 16:15 ../7_Ft_printf_wit
// h_Petr
// -rw-r--r--   1 sschmele  2018              10698 Jun  7 11:33 ./README.md
// crw-rw----   1 root      _windowserver   19,   0 Jun 15 16:49 /dev/xcpm

											// at-e4% ./ft_ls -dl ./README.md ../7_Ft_printf_with_Petr /dev/xcpm

// drwxr-xr-x  16 sschmele  2018                544 Apr 27 16:15 ../7_Ft_printf_wit
// h_Petr
// -rw-r--r--   1 sschmele  2018              10698 Jun  7 11:33 ./README.md
// crw-rw----   1 root      _windowserver   19,   0 Jun 15 16:49 /dev/xcpm

											// at-e4% ./ft_ls -dl ./README.md ../7_Ft_printf_with_Petr /dev/ttyp4

// drwxr-xr-x  16 sschmele  2018       544 Apr 27 16:15 ../7_Ft_printf_with_Petr
// -rw-r--r--   1 sschmele  2018     10698 Jun  7 11:33 ./README.md

											// crw-rw-rw-   1 root      wheel   4,   4 Jun 15 16:49 /dev/ttyp4

// at-e4% ls -dl ./README.md ../7_Ft_printf_with_Petr /dev/ttyp4
// drwxr-xr-x  16 sschmele  2018        544 Apr 27 16:15 ../7_Ft_printf_with_Petr
// -rw-r--r--   1 sschmele  2018      10698 Jun  7 11:33 ./README.md
// crw-rw-rw-   1 root      wheel    4,   4 Jun 15 16:49 /dev/ttyp4

// t-e4% ls -l /dev/tty
// crw-rw-rw-  1 root  wheel    2,   0 Jun 15 16:49 /dev/tty
// at-e4% ./ft_ls -l /dev/tty
// crw-rw-rw-  1 root  wheel   2,   0 Jun 15 16:49 /dev/tty

void				print_stackfile(t_file *file, int *col)
{
	int				i;
	void			**ptr;

	i = 1;
	ptr = (void **)&file->total;
	while (++i < 9)
	{
		if (col[i])
		{
			if (i == 5)
				buf_fill(((struct passwd *)*ptr)->pw_name,
				ft_strlen(((struct passwd *)*ptr)->pw_name), col[i], 1);
			else if (i == 6)
				buf_fill(((struct group *)*ptr)->gr_name,
				ft_strlen(((struct group *)*ptr)->gr_name), col[i], 1);
			else if (i == 7)
				buf_fill(file->size, ft_strlen(file->size), col[i], 0);
			else
				buf_fill(*ptr, ft_strlen(*ptr), col[i], i == 3 ? 1 : 0);
			(i == 5 || i == 6) ? buf_add("  ", 2) : buf_add(" ", 1);
			
		}
		++ptr;
	}
	buf_add(file->color, 9);
	buf_add(file->name, ft_strlen(file->name));
	buf_add("\n", 1);
}

void		separate_output(int flags, int *columns)
{
	if (flags & FLAG_ATTY)
		columns[9] = get_terminal_width();
	else
		columns[9] = 80;
	if (flags & FLAG_CC)
	{
		if (~flags & FLAG_GG)
			while (columns[10] % 8 != 0)
				columns[10]++;
		else if (((flags & FLAG_GG) && (flags & FLAG_P)) || ((flags & FLAG_GG) && (flags & FLAG_FF)))
			columns[10] += 2;
		else
			columns[10] += 1; // если есть G флаг, длина колонка 10 другая = самое длинное название + 1 пробел)
		if (flags & FLAG_S)
			columns[10] += columns[2] + 1; //один пробел между
	}
}

int			get_terminal_width(void)
{
	struct winsize	sz;

	ioctl(1, TIOCGWINSZ, &sz);
	return (sz.ws_col);
}
