/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorwin <jcorwin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 02:00:05 by jcorwin           #+#    #+#             */
/*   Updated: 2019/05/28 13:49:01 by jcorwin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

// static void		print_file(t_file *file, int *flags)
// {
// 	buf_add(file->name, ft_strlen(file->name));
// 	buf_add("\n", 1);
// }

static void		print_file(t_file *file, int *col)
{
	int		i;
	void	**ptr;

	i = 0;
	ptr = &file->uid;
	while (++i < 7)
		if (col[i])
		{
			if (i > 2)
				buf_fill(*ptr, ft_strlen(*ptr), col[i], 0);
			else if (i == 2)
				buf_fill(((struct passwd *)*ptr)->pw_name,
				ft_strlen(((struct passwd *)*ptr)->pw_name), col[i], 1);
			else if (i == 3)
				buf_fill(((struct group *)*ptr)->gr_name,
				ft_strlen(((struct group *)*ptr)->gr_name), col[i], 1);
			++ptr;
			if ((i == 1 && col[1] == 11) || i > 5)
				buf_add(" ", 1);
			else
				buf_add("  ", 2);
		}
	buf_add(file->name, ft_strlen(file->name));
	buf_add("\n", 1);
}

void			print_files(t_stack *files, int flags)
{
	int		columns[7];
	
	// ST_ITER(files, (void (*)(void *, void *))print_file, &flags, flags & FLAG_R);
	ST_ITER(files, (void (*)(void *, void *))print_file, columns, flags & FLAG_R);
}
