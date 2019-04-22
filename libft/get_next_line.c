/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/28 20:33:00 by sschmele          #+#    #+#             */
/*   Updated: 2019/03/19 11:45:10 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int				next_buf(char *content)
{
	char				*tmp;

	if (!(tmp = ft_strchrnew(content, '\n')))
		return (-1);
	ft_strclr(content);
	if (ft_strlen(tmp) > 0)
	{
		ft_strcpy(content, tmp);
		free(tmp);
		return (0);
	}
	free(tmp);
	return (1);
}

static int				check(char *content, char **line)
{
	char				*p;
	char				flag;
	int					i;

	flag = 0;
	i = 0;
	if (ft_strlen(content) > 0)
	{
		if (content[0] == '\n')
		{
			flag++;
			ft_strcpy(content, content + 1);
		}
		if (flag > 0)
			return (0);
		if (!(p = ft_strndup(content, ft_strchrlen(content, '\n'))))
			return (-1);
		if (!(*line = ft_strrejoin(*line, p)))
			return (-1);
		free(p);
		if (next_buf(content) == 0)
			return (0);
	}
	return (1);
}

static int				read_and_return(t_list *tmp, const int fd, char **line)
{
	int					iread;
	char				*temp;

	if (!(*line = ft_memalloc(1)))
		return (-1);
	if (check(tmp->content, line) == 0)
		return (1);
	while ((iread = read(fd, tmp->content, BUFF_SIZE)) == BUFF_SIZE)
	{
		if ((temp = ft_strchr(tmp->content, '\n')) != 0)
			break ;
		if (!(*line = ft_strrejoin(*line, tmp->content)))
			return (-1);
	}
	ft_strclr(tmp->content + iread);
	check(tmp->content, line);
	if (iread == 0 && ft_strlen(*line) == 0)
		return (0);
	return (1);
}

int						get_next_line(const int fd, char **line)
{
	static t_list		*first_list;
	t_list				*list;

	if (line == NULL || (read(fd, *line, 0) < 0))
		return (-1);
	list = first_list;
	while (list)
	{
		if ((int)list->content_size == (int)fd)
			return (read_and_return(list, fd, line));
		list = list->next;
	}
	if (!(list = (t_list*)malloc(sizeof(t_list))))
	{
		free(list);
		return (-1);
	}
	if (!(list->content = ft_strnew(BUFF_SIZE)))
	{
		free(list);
		return (-1);
	}
	list->content_size = fd;
	ft_lstadd(&first_list, list);
	return (read_and_return(list, fd, line));
}
