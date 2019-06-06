/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_stackfile.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 02:00:05 by jcorwin           #+#    #+#             */
/*   Updated: 2019/06/06 15:03:30 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void				print_stackfile(t_file *file, int *col) //26 lines
{
	int				i;
	void			**ptr;

	i = 1;
	ptr = (void **)&file->total;
	while (++i < 11)
	{
		if (col[i])
		{
			if (i == 5)
				buf_fill(((struct passwd *)*ptr)->pw_name,
				ft_strlen(((struct passwd *)*ptr)->pw_name), col[i], 1);
			else if (i == 6)
				buf_fill(((struct group *)*ptr)->gr_name,
				ft_strlen(((struct group *)*ptr)->gr_name), col[i], 1);
			else
				buf_fill(*ptr, ft_strlen(*ptr), col[i], i == 3 ? 1 : 0);
			if (i == 5 || i == 6)
				buf_add("  ", 2);
			else
				buf_add(" ", 1);
		}
		++ptr;
	}
	buf_add(file->name, ft_strlen(file->name));
	buf_add("\n", 1);
}

static int			get_terminal_width(void)
{
	struct winsize	sz;

	ioctl(1, TIOCGWINSZ, &sz);
	return (sz.ws_col);
}
