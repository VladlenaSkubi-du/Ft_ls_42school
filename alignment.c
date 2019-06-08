/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alignment.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschmele <sschmele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 11:38:48 by sschmele          #+#    #+#             */
/*   Updated: 2019/06/08 18:28:32 by sschmele         ###   ########.fr       */
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
	tmp = max;
	while (tmp % 8 != 0)
		tmp++;
	bla->x = term / tmp; //columns
	if (nb % bla->x == 0)
		bla->y = nb / bla->x;
	else
		bla->y = nb / bla->x + 1;
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
    //t_point size = { 22, 16 };
	// t_point size = { 6, 3 };
	t_point size = { 30, 15 };
	// t_point size = { 30, 332 };
	t_point *final;
	int		terminal;
    // char    *zone[] = {"1_Piscine",
	// 					"2_Preparation",
	// 					"3_LIBFT",
	// 					"4_Get_next_line_w",
	// 					"5_Fillit_w", 
	// 					"6_Init_w", 
	// 					"7_Ft_printf_with_Petr", 
	// 					"8_Ft_ls_mygit", 
	// 					"README_good_example.md", 
	// 					"TMP_LS", 
	// 					"challenge00.c", 
	// 					"challenge01.c", 
	// 					"ft_quick_sort.c", 
	// 					"headerhodor.h", 
	// 					"library.c", 
	// 					"temporal"};

	// char    *zone[] = {".",
    //                      "..",
	// 					 "a.out" };

	char    *zone[] = {	".",
						"..",
						"errors.c",
						"fill_stackfiles_info_1.c",
						"fill_stackfiles_info_2.c",
						"main.c",
						"new.txt",
						"other_functions.c",
						"out_buf.c",
						"parser.c",
						"print_stackfile.c",
						"read_dir.c",
						"sort_by_flags.c",
						"stack_add_iter_del.c",
						"stack_sort.c"};
	
	// char    *zone[] = {	"afsc_type5",
	// 					"auditpipe",
	// 					"auditsessions",
	// 					"autofs",
	// 					"autofs_control",
	// 					"autofs_homedirmounter",
	// 					"autofs_notrigger",
	// 					"autofs_nowait",
	// 					"bpf0",
	// 					"bpf1",
	// 					"bpf2",
	// 					"bpf3",
	// 					"console",
	// 					"cu.-CSRGAIA",
	// 					"cu.BRN-HDW03-BK-SerialPort",
	// 					"cu.Bluetooth-Incoming-Port",
	// 					"cu.MallieBeahansAirPods-Wi",
	// 					"cu.iPhone-WirelessiAPv2",
	// 					"disk0",
	// 					"disk0s1",
	// 					"disk0s2",
	// 					"disk0s3",
	// 					"disk0s4",
	// 					"disk0s5",
	// 					"disk1",
	// 					"disk1s1",
	// 					"disk1s2",
	// 					"disk2",
	// 					"dtrace",
	// 					"dtracehelper",
	// 					"fbt",
	// 					"fd",
	// 					"fsevents",
	// 					"io8log",
	// 					"io8logmt",
	// 					"io8logtemp",
	// 					"lockstat",
	// 					"machtrace",
	// 					"null",
	// 					"oslog",
	// 					"oslog_stream",
	// 					"pf",
	// 					"pfm",
	// 					"profile",
	// 					"ptmx",
	// 					"ptyp0",
	// 					"ptyp1",
	// 					"ptyp2",
	// 					"ptyp3",
	// 					"ptyp4",
	// 					"ptyp5",
	// 					"ptyp6",
	// 					"ptyp7",
	// 					"ptyp8",
	// 					"ptyp9",
	// 					"ptypa",
	// 					"ptypb",
	// 					"ptypc",
	// 					"ptypd",
	// 					"ptype",
	// 					"ptypf",
	// 					"ptyq0",
	// 					"ptyq1",
	// 					"ptyq2",
	// 					"ptyq3",
	// 					"ptyq4",
	// 					"ptyq5",
	// 					"ptyq6",
	// 					"ptyq7",
	// 					"ptyq8",
	// 					"ptyq9",
	// 					"ptyqa",
	// 					"ptyqb",
	// 					"ptyqc",
	// 					"ptyqd",
	// 					"ptyqe",
	// 					"ptyqf",
	// 					"ptyr0",
	// 					"ptyr1",
	// 					"ptyr2",
	// 					"ptyr3",
	// 					"ptyr4",
	// 					"ptyr5",
	// 					"ptyr6",
	// 					"ptyr7",
	// 					"ptyr8",
	// 					"ptyr9",
	// 					"ptyra",
	// 					"ptyrb",
	// 					"ptyrc",
	// 					"ptyrd",
	// 					"ptyre",
	// 					"ptyrf",
	// 					"ptys0",
	// 					"ptys1",
	// 					"ptys2",
	// 					"ptys3",
	// 					"ptys4",
	// 					"ptys5",
	// 					"ptys6",
	// 					"ptys7",
	// 					"ptys8",
	// 					"ptys9",
	// 					"ptysa",
	// 					"ptysb",
	// 					"ptysc",
	// 					"ptysd",
	// 					"ptyse",
	// 					"ptysf",
	// 					"ptyt0",
	// 					"ptyt1",
	// 					"ptyt2",
	// 					"ptyt3",
	// 					"ptyt4",
	// 					"ptyt5",
	// 					"ptyt6",
	// 					"ptyt7",
	// 					"ptyt8",
	// 					"ptyt9",
	// 					"ptyta",
	// 					"ptytb",
	// 					"ptytc",
	// 					"ptytd",
	// 					"ptyte",
	// 					"ptytf",
	// 					"ptyu0",
	// 					"ptyu1",
	// 					"ptyu2",
	// 					"ptyu3",
	// 					"ptyu4",
	// 					"ptyu5",
	// 					"ptyu6",
	// 					"ptyu7",
	// 					"ptyu8",
	// 					"ptyu9",
	// 					"ptyua",
	// 					"ptyub",
	// 					"ptyuc",
	// 					"ptyud",
	// 					"ptyue",
	// 					"ptyuf",
	// 					"ptyv0",
	// 					"ptyv1",
	// 					"ptyv2",
	// 					"ptyv3",						
	// 					"tyv4",
	// 					"ptyv5",
	// 					"ptyv6",
	// 					"ptyv7",
	// 					"ptyv8",
	// 					"ptyv9",
	// 					"ptyva",
	// 					"ptyvb",
	// 					"ptyvc",
	// 					"ptyvd",
	// 					"ptyve",
	// 					"ptyvf",
	// 					"ptyw0",
	// 					"ptyw1",
	// 					"ptyw2",
	// 					"ptyw3",
	// 					"ptyw4",
	// 					"ptyw5",
	// 					"ptyw6",
	// 					"ptyw7",
	// 					"ptyw8",
	// 					"ptyw9",
	// 					"ptywa",
	// 					"ptywb",
	// 					"ptywc",
	// 					"ptywd",
	// 					"ptywe",
	// 					"ptywf",
	// 					"random",
	// 					"rdisk0",
	// 					"rdisk0s1",
	// 					"rdisk0s2",
	// 					"rdisk0s3",
	// 					"rdisk0s4",
	// 					"rdisk0s5",
	// 					"rdisk1",
	// 					"rdisk1s1",
	// 					"rdisk1s2",
	// 					"rdisk2",
	// 					"sdt",
	// 					"stderr",
	// 					"stdi",
	// 					"stdout",
	// 					"systrace",
	// 					"tty",
	// 					"tty.-CSRGAIA",
	// 					"tty.BRN-HDW03-BK-SerialPort",
	// 					"tty.Bluetooth-Incoming-Port",
	// 					"tty.MallieBeahansAirPods-Wi",
	// 					"tty.iPhone-WirelessiAPv2",
	// 					"ttyp0",
	// 					"ttyp1",
	// 					"ttyp2",
	// 					"ttyp3",
	// 					"ttyp4",
	// 					"ttyp5",
	// 					"ttyp6",
	// 					"ttyp7",
	// 					"ttyp8",
	// 					"ttyp9",
	// 					"ttypa",
	// 					"ttypb",
	// 					"ttypc",
	// 					"ttypd",
	// 					"ttype",
	// 					"ttypf",
	// 					"ttyq0",
	// 					"ttyq1",
	// 					"ttyq2",
	// 					"ttyq3",
	// 					"ttyq4",
	// 					"ttyq5",
	// 					"ttyq6",
	// 					"ttyq7",
	// 					"ttyq8",
	// 					"ttyq9",
	// 					"ttyqa",
	// 					"ttyqb",
	// 					"ttyqc",
	// 					"ttyqd",
	// 					"ttyqe",
	// 					"ttyqf",
	// 					"ttyr0",
	// 					"ttyr1",
	// 					"ttyr2",
	// 					"ttyr3",
	// 					"ttyr4",
	// 					"ttyr5",
	// 					"ttyr6",
	// 					"ttyr7",
	// 					"ttyr8",
	// 					"ttyr9",
	// 					"ttyra",
	// 					"ttyrb",
	// 					"ttyrc",
	// 					"ttyrd",
	// 					"ttyre",
	// 					"ttyrf",
	// 					"ttys0",
	// 					"ttys000",
	// 					"ttys001",
	// 					"ttys004",
	// 					"ttys1",
	// 					"ttys2",
	// 					"ttys3",
	// 					"ttys4",
	// 					"ttys5",
	// 					"ttys6",
	// 					"ttys7",
	// 					"ttys8",
	// 					"ttys9",
	// 					"ttysa",
	// 					"ttysb",
	// 					"ttysc",
	// 					"ttysd",
	// 					"ttyse",
	// 					"ttysf",
	// 					"ttyt0",
	// 					"ttyt1",
	// 					"ttyt2",
	// 					"ttyt3",
	// 					"ttyt4",
	// 					"ttyt5",
	// 					"ttyt6",
	// 					"ttyt7",
	// 					"ttyt8",
	// 					"ttyt9",
	// 					"ttyta",
	// 					"ttytb",
	// 					"ttytc",
	// 					"ttytd",
	// 					"ttyte",
	// 					"ttytf",
	// 					"ttyu0",
	// 					"ttyu1",
	// 					"ttyu2",
	// 					"ttyu3",
	// 					"ttyu4",
	// 					"ttyu5",
	// 					"ttyu6",
	// 					"ttyu7",
	// 					"ttyu8",
	// 					"ttyu9",
	// 					"ttyua",
	// 					"ttyub",
	// 					"ttyuc",
	// 					"ttyud",
	// 					"ttyue",
	// 					"ttyuf",
	// 					"ttyv0",
	// 					"ttyv1",
	// 					"ttyv2",
	// 					"ttyv3",
	// 					"ttyv4",
	// 					"ttyv5",
	// 					"ttyv6",
	// 					"ttyv7",
	// 					"ttyv8",
	// 					"ttyv9",
	// 					"ttyva",
	// 					"ttyvb",
	// 					"ttyvc",
	// 					"ttyvd",
	// 					"ttyve",
	// 					"ttyvf",
	// 					"ttyw0",
	// 					"ttyw1",
	// 					"ttyw2",
	// 					"ttyw3",
	// 					"ttyw4",
	// 					"ttyw5",
	// 					"ttyw6",
	// 					"ttyw7",
	// 					"ttyw8",
	// 					"ttyw9",
	// 					"ttywa",
	// 					"ttywb",
	// 					"ttywc",
	// 					"ttywd",
	// 					"ttywe",
	// 					"ttywf",
	// 					"urandom",
	// 					"vboxdrv",
	// 					"vboxdrvu",
	// 					"vboxnetctl",
	// 					"xcpm",
	// 					"zero"};

    area = make_area(zone, size);
    //print_tab(area, size);
	printf("terminal: %d\n", terminal = get_terminal_width());
	final = find_columns(size.x, terminal, size.y);
	print_out(area, final, terminal, size.x);
    return (0);
}