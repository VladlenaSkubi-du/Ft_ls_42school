/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alignment.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 11:38:48 by sschmele          #+#    #+#             */
/*   Updated: 2019/06/07 16:24:10 by sschmele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>

typedef struct	s_point
{
	int			x;
	int			y;
}				t_point;

void				print_out(char **area, t_point *final, int term, int max)
{
	int		i = 0;
	int		j = 0;
	int		tmp = 1;
	int		tmp_2 = 0;
	char	**pr;

	pr = (char**)malloc(final->y + 1);
	pr[final->y] = 0;
	while (i < final->y)
	{
		pr[i] = (char*)malloc(term + 1);
		while (j < term)
		{
			pr[i][j] = '0';
			j++;
		}
		while (tmp < final->x)
		{
			pr[i][max * tmp + tmp_2] = ' ';
			pr[i][max * tmp + tmp_2 + 1] = ' ';
			tmp++;
			tmp_2 += 2;
		}
		printf("%s\n", pr[i]);
		tmp = 1;
		tmp_2 = 0;
		j = 0;
		i++;
	}
	i = 0;
	j = 0;
}

t_point				*find_columns(int max, int term, int nb)
{
	t_point		*bla;
	int		can;
	int		tmp;

	
	bla = (t_point*)malloc(sizeof(t_point));
	tmp = term / (max + 2);
	if (term % (max + 2) != 0)
		bla->x = tmp;
	else
		bla->x = tmp - 1;
	bla->y = nb / bla->x + 1; // (в столбце)
	printf("tmp: %d	bla->x and bla->y: %d	%d\n", tmp, bla->x, bla->y);
	return (bla);
}

static int			get_terminal_width(void)
{
	struct winsize	sz;

	ioctl(1, TIOCGWINSZ, &sz);
	return (sz.ws_col);
}

size_t			ft_strlen(const char *s)
{
	size_t			*iter;
	unsigned char	*end;

	if (!s)
		return (0);
	end = (unsigned char *)s;
	while ((size_t)end % sizeof(size_t))
		if (!(*end++))
			return (end - (unsigned char *)s - 1);
	iter = (size_t *)end;
	while ((*iter - 0x0101010101010101 & ~(*iter) & 0x8080808080808080) == 0)
		iter++;
	end = (unsigned char *)iter;
	while (*end)
		++end;
	return (end - (unsigned char *)s);
}

int		find_len(char **area)
{
	size_t	res = 1;
	int		i = 0;
	size_t	tmp;

	while (area[i])
	{
		if ((tmp = ft_strlen(area[i])) > res)
			res = tmp;
		i++;
	}
	return ((int)res);
}

void	print_tab(char **area, t_point size)
{
	int		i;
	int		j;

	i = -1;
	j = -1;
	while (++i < size.y)
	{
		while (area[i][++j])
			write(1, &area[i][j], 1);
        write(1, "\n", 1);
		j = -1;
	}
}

char	**make_area(char **zone, t_point size)
{
	char	**ar;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!(ar = (char**)malloc(sizeof(char*) * size.y + 1)))
		return (NULL);
	ar[size.y] = 0;
	while (i < size.y)
	{
		if (!(ar[i] = malloc(size.x + 1)))
		{
			while (--i >= 0)
				free(ar[i]);
			free(ar);
			return (NULL);
		}
		ar[i][size.y] = '\0';
		while (j < size.x)
		{
			ar[i][j] = zone[i][j];
			j++;
		}
		j = 0;
		i++;
	}
	return (ar);
}

int main(void)
{
    char 	**area;
    t_point size = { 15, 20 };
	// t_point size = { 6, 3 };
	t_point *final;
	int		max_len;
	int		terminal;
    char    *zone[] = {"-a",
                        "Makefile",
                        "README.md",
                        "TEST_M",
                        "alignment.c",
                        "author",
                        "colors.c",
                        "ft_ls",
                        "ft_ls.dSYM",
                        "includes",
                        "libft",
                        "norm_script.sh",
                        "objs",
                        "print.c",
                        "srcs",
                        "t1",
                        "t2",
                        "t_our.txt",
                        "test1",
                        "tmp"};
	// char    *zone[] = {".",
    //                      "..",
	// 					 "a.out" };
    area = make_area(zone, size);
    //print_tab(area, size);
	printf("max length: %d\n", max_len = find_len(area));
	printf("terminal: %d\n", terminal = get_terminal_width());
	final = find_columns(max_len, terminal, 20);
	print_out(area, final, terminal, max_len);
    return (0);
}