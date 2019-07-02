/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_stackfile.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorwin <jcorwin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 02:00:05 by jcorwin           #+#    #+#             */
/*   Updated: 2019/07/02 12:57:44 by jcorwin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		print_stackfile(t_file *file, int *col)
{
	int				i;
	void			**ptr;

	i = 1;
	ptr = (void **)&file->total - 1;
	while (++i < 9 && ++ptr)
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
	((col[0] & FLAG_GG) && (col[0] & FLAG_ATTY)) ? buf_add(file->color, 12) : 0;
	buf_add(file->name, ft_strlen(file->name));
	buf_add("\n", 1);
}

/*
**If there is a G-flag, the tabs after file-names are changed to one space;
**If the term-width is too narrow, C-flag is turned off and a -1 flag is
**turned on;
**If there are changes in longest file-name after the change_name function
**(these are -F and -p flags), one space to columns[10] (output-columns width
**for -C flag) is added.
*/

void		separate_output(int *flags, int *columns)
{
	columns[9] = (*flags & FLAG_ATTY) ? get_terminal_width() : 80;
	if (columns[9] < columns[10] * 2)
	{
		*flags ^= FLAG_CC;
		*flags |= FLAG_ONE;
	}
	if (*flags & FLAG_CC)
	{
		if (~*flags & FLAG_GG)
			while (columns[10] % 8 != 0)
				columns[10]++;
		else if (((*flags & FLAG_GG) && (*flags & FLAG_P)) ||
		((*flags & FLAG_GG) && (*flags & FLAG_FF)))
			columns[10] += 2;
		else
			columns[10] += 1;
		if (*flags & FLAG_S)
			columns[10] += columns[2] + 1;
	}
}

int			get_terminal_width(void)
{
	struct winsize	sz;

	ioctl(1, TIOCGWINSZ, &sz);
	return (sz.ws_col);
}
