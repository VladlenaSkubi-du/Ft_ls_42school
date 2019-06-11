/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 20:33:03 by sschmele          #+#    #+#             */
/*   Updated: 2019/06/11 17:33:45 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

//ЕЩЕ ТАБ МЕНЯЕТСЯ НА ПРОБЕЛ!!!

static void        color_regular_stackfiles(t_file *file, char *before)
{
    if (file->mode[3] == 's')
            ft_strcpy(before, "\033[30;41m");
        else if (file->mode[3] == 'S' && ((file->mode[6] == 'x'
            || file->mode[6] == 'S' || file->mode[6] == 's')
            || file->mode[9] == 'x'))
            ft_strcpy(before, "\033[30;41m");
        if (file->mode[6] == 's' && (!(file->mode[3] == 's'
            || file->mode[3] == 'S')))
            ft_strcpy(before, "\033[30;46m");
        else if (file->mode[6] == 'S' && (file->mode[3] == 'x'
            || file->mode[9] == 'x'))
            ft_strcpy(before, "\033[30;46m");
        if ((file->mode[3] == 'x' || file->mode[6] == 'x'
            || file->mode[9] == 'x') && (!(file->mode[3] == 's'
            || file->mode[3] == 'S' || file->mode[6] == 's'
            || file->mode[6] == 'S')))
            ft_strcpy(before, "\033[31m");
}

void        color_stackfiles(t_file *file)
{
    char    *before;
    char    *after;
    
    before = (char*)ft_xmalloc(15);
    after = (char*)ft_xmalloc(15);
                                                                //printf("here\n");
    ft_strcpy(after, "\033[0m"); //без этого получится фигня
    if (file->type == 'l') //но только название самой ссылки
        ft_strcpy(before, "\033[35m");
    else if (file->type == 'c')
        ft_strcpy(before, "\033[34;43m");
    else if (file->type == 'b')
        ft_strcpy(before, "\033[34;46m");
    else if (file->type == 's')
        ft_strcpy(before, "\033[32m");
    else if (file->type == 'p')
        ft_strcpy(before, "\033[33m");
    else if (file->type == 'd')
    {
        if (file->mode[8] == 'w' &&
            (file->mode[9] == 't' || file->mode[9] == 'T'))
            ft_strcpy(before, "\033[30;42m");
        else
            ft_strcpy(before, "\033[34m");
    }
    else if (file->type == '-')
        color_regular_stackfiles(file, before);
    printf("%s%s:%s%s\n", before, file->mode, file->name, after);
}