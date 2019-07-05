/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 18:33:30 by sschmele          #+#    #+#             */
/*   Updated: 2019/07/05 14:25:55 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	usage(void)
{
	buf_err("usage: ft_ls [-1lrRatGpsufdgSCcF] [file ...]\n");
	exit(0);
}

void	print_err(char *dirname)
{
	buf_err("ft_ls: ");
	buf_err(dirname);
	if (errno == EACCES)
		buf_err(": Permission denied\n");
	else if (errno == ENOENT)
		buf_err(": No such file or directory\n");
}

void	ft_printerr(char *str, size_t size)
{
	write(2, str, size);
}

void	buf_err(char *str)
{
	buf_add(NULL, 0);
	ft_printerr(str, ft_strlen(str));
}
