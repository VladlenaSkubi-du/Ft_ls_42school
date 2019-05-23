/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorwin <jcorwin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 02:00:05 by jcorwin           #+#    #+#             */
/*   Updated: 2019/05/23 10:07:14 by jcorwin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		print_file(t_file *file, int *flags)
{
	buf_add(file->name, ft_strlen(file->name));
	buf_add("\n", 1);
}

void			print_files(t_stack *files, int flags)
{
	ST_ITER(files, (void (*)(void *, void *))print_file, &flags, flags & FLAG_R);
}
