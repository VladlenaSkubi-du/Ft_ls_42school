# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jcorwin <jcorwin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/04 16:34:17 by sschmele          #+#    #+#              #
#    Updated: 2019/05/13 19:30:45 by sschmele         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
FLAGS = -Wall -Wextra -Werror
SRCS = ./ft_atoi.c \
	   ./ft_bzero.c \
	   ./ft_isalnum.c \
	   ./ft_isalpha.c \
	   ./ft_isascii.c \
	   ./ft_isdigit.c \
	   ./ft_isprint.c \
	   ./ft_memccpy.c \
	   ./ft_memchr.c \
	   ./ft_memcmp.c \
	   ./ft_memcpy.c \
	   ./ft_memmove.c \
	   ./ft_memset.c \
	   ./ft_strcat.c \
	   ./ft_strchr.c \
	   ./ft_strchri.c \
	   ./ft_strcmp.c \
	   ./ft_strcpy.c \
	   ./ft_strdup.c \
	   ./ft_strlcat.c \
	   ./ft_strlen.c \
	   ./ft_strncat.c \
	   ./ft_strncmp.c \
	   ./ft_strncpy.c \
	   ./ft_strnstr.c \
	   ./ft_strrchr.c \
	   ./ft_strstr.c \
	   ./ft_tolower.c \
	   ./ft_toupper.c \
	   ./ft_itoa.c \
	   ./ft_makerevstr.c \
	   ./ft_memalloc.c \
	   ./ft_memdel.c \
	   ./ft_nb_root.c \
	   ./ft_putchar.c \
	   ./ft_putchar_fd.c \
	   ./ft_putendl.c \
	   ./ft_putendl_fd.c \
	   ./ft_putnbr.c \
	   ./ft_putnbr_fd.c \
	   ./ft_putstr.c \
	   ./ft_putstr_fd.c \
	   ./ft_strclr.c \
	   ./ft_strdel.c \
	   ./ft_strequ.c \
	   ./ft_striter.c \
	   ./ft_striteri.c \
	   ./ft_strjoin.c \
	   ./ft_strmap.c \
	   ./ft_strmapi.c \
	   ./ft_strndup.c \
	   ./ft_strnequ.c \
	   ./ft_strnew.c \
	   ./ft_strsplit.c \
	   ./ft_strsub.c \
	   ./ft_strtrim.c \
	   ./ft_lstadd.c \
	   ./ft_lstdel.c \
	   ./ft_lstdelone.c \
	   ./ft_lstiter.c \
	   ./ft_lstmap.c \
	   ./ft_lstnew.c \
	   ./ft_lstlast.c \
	   ./ft_lstsize.c \
	   ./ft_bubble_sort.c \
	   ./ft_choice_sort.c \
	   ./ft_nputstr.c \
	   ./ft_insertive_sort.c \
	   ./ft_strchrlen.c \
	   ./ft_strrejoin.c \
	   ./ft_strchrnew.c \
	   ./ft_lstdelcont.c \
	   ./ft_mapdel.c \
	   ./ft_printmap.c \
	   ./ft_ltoa_base.c \
	   ./ft_strnewsetchar.c \
	   ./ft_restrsub.c \
	   ./ft_utoa_base.c \
	   ./get_next_line.c

DIR_O = objs
OBJS = $(addprefix $(DIR_O)/,$(SRCS:.c=.o))

INCLUDE = includes/libft.h

all:		$(NAME)

$(NAME):	text $(OBJS)
			@make -C ./ft_printf
			@cp ft_printf/libftprintf.a $(NAME)
			@ar rc $(NAME) $(OBJS)
			@ranlib $(NAME)
			@echo "\x1b[32;01mYour libft.a is ready.\x1b[32;01m"

$(OBJS):	$(DIR_O)/%.o: %.c $(INCLUDE)
			@mkdir -p $(DIR_O)
			@gcc $(FLAGS) -c -I includes -o $@ $<

text:
			@echo "\x1b[32;01mCompiling libft...\x1b[32;01m"

clean:
			@echo "\033[34mDeliting libft o-files\033[34m"
			@make clean --directory ./ft_printf
			@/bin/rm -rf $(DIR_O)

fclean:	clean
			@echo "\033[34mDeliting libft.a\033[34m"
			@make fclean --directory ./ft_printf
			@/bin/rm -f $(NAME)

re: 	fclean all

.PHONY: all text clean fclean
