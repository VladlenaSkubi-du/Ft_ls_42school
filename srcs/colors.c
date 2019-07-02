/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 20:33:03 by sschmele          #+#    #+#             */
/*   Updated: 2019/07/02 17:03:42 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void			color_regular_stackfiles(t_file *file)
{
	if (file->mode[3] == 's')
		ft_strcpy(file->color, "\033[00;30;41m");
	else if (file->mode[3] == 'S' && ((file->mode[6] == 'x'
				|| file->mode[6] == 'S' || file->mode[6] == 's')
				|| file->mode[9] == 'x'))
		ft_strcpy(file->color, "\033[00;30;41m");
	if (file->mode[6] == 's' && (!(file->mode[3] == 's'
				|| file->mode[3] == 'S')))
		ft_strcpy(file->color, "\033[00;30;46m");
	else if (file->mode[6] == 'S' && (file->mode[3] == 'x'
				|| file->mode[9] == 'x'))
		ft_strcpy(file->color, "\033[00;30;46m");
	if ((file->mode[3] == 'x' || file->mode[6] == 'x'
				|| file->mode[9] == 'x') && (!(file->mode[3] == 's'
				|| file->mode[3] == 'S' || file->mode[6] == 's'
				|| file->mode[6] == 'S')))
		ft_strcpy(file->color, "\033[00;00;31m");
	else
		ft_strcpy(file->color, "\033[00;00;00m");
}

void				color_stackfiles(t_file *file)
{
	if (file->type == 'l')
		ft_strcpy(file->color, "\033[00;00;35m");
	else if (file->type == 'c')
		ft_strcpy(file->color, "\033[00;34;43m");
	else if (file->type == 'b')
		ft_strcpy(file->color, "\033[00;34;46m");
	else if (file->type == 's')
		ft_strcpy(file->color, "\033[00;00;32m");
	else if (file->type == 'p')
		ft_strcpy(file->color, "\033[00;00;33m");
	else if (file->type == 'd')
	{
		if (file->mode[8] == 'w' && 
				(file->mode[9] == 't' || file->mode[9] == 'T'))
			ft_strcpy(file->color, "\033[00;30;42m");
		else if (file->mode[8] == 'w')
			ft_strcpy(file->color, "\033[00;30;43m");
		else
			ft_strcpy(file->color, "\033[00;00;34m");
	}
	else if (file->type == '-')
		color_regular_stackfiles(file);
	else
		ft_strcpy(file->color, "\033[00;00;00m");
	file->name = ft_strrejoin(file->name, "\033[0m");
}
