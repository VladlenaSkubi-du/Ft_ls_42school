/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorwin <jcorwin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 20:33:03 by sschmele          #+#    #+#             */
/*   Updated: 2019/06/30 20:14:05 by jcorwin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

//ЕЩЕ ТАБ МЕНЯЕТСЯ НА ПРОБЕЛ!!!

static void        color_regular_stackfiles(t_file *file)
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
        ft_strcpy(file->color, "\033[00;31;40m");
    else
        ft_strcpy(file->color, "\033[00;37;40m");
    
}

void        color_stackfiles(t_file *file)
{
    // char    *after;
    // after = (char*)ft_xmalloc(15);
    //                                                             //printf("here\n");
    // ft_strcpy(after, "\033[0m"); //без этого получится фигня
    if (file->type == 'l') //но только название самой ссылки
        ft_strcpy(file->color, "\033[00;35;40m");
    else if (file->type == 'c')
        ft_strcpy(file->color, "\033[00;34;43m");
    else if (file->type == 'b')
        ft_strcpy(file->color, "\033[00;34;46m");
    else if (file->type == 's')
        ft_strcpy(file->color, "\033[00;32;40m");
    else if (file->type == 'p')
        ft_strcpy(file->color, "\033[00;33;40m");
    else if (file->type == 'd')
    {
        if (file->mode[8] == 'w' &&
            (file->mode[9] == 't' || file->mode[9] == 'T'))
            ft_strcpy(file->color, "\033[00;30;42m");
        else
            ft_strcpy(file->color, "\033[01;96;40m");
    }
    else if (file->type == '-')
        color_regular_stackfiles(file);
    else
        ft_strcpy(file->color, "\033[00;37;40m");
    
    // printf("%s%s:%s\n", file->color, file->mode, file->name);
}