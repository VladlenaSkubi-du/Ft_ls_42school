NAME = ft_ls

#FLAGS = -Wall -Werror -Wextra

SOURCES =	main.c \
			parser.c \
			stack_add_iter_del.c \
			stack_sort.c \
			read_dir.c \
			sort_by_flags.c \
			fill_stackfiles_info_1.c \
			fill_stackfiles_info_2.c \
			print_stackfile.c \
			out_buf.c \
			errors.c \
			other_functions.c

DIR_O = objs

DIR_S = srcs

SRCS = $(addprefix $(DIR_S)/,$(SOURCES))

OBJS = $(addprefix $(DIR_O)/,$(SOURCES:.c=.o))

LIBFT = libft/libft.a

all:	$(NAME)

$(NAME):		text $(OBJS)
				@make -C ./libft
				@gcc $(FLAGS) $(OBJS) -o $(NAME) libft/libft.a
				@echo "\x1b[32;01mYour ft_ls is ready\x1b[32;01m"

text:
				@echo "\x1b[32;01mCompiling your ft_ls...\x1b[32;01m"

$(OBJS):		$(DIR_O)/%.o: $(DIR_S)/%.c includes/ft_ls.h
				@mkdir -p $(DIR_O)
				gcc $(FLAGS) -c -I includes -o $@ $<
clean:
				@echo "\033[34mDeliting ft_ls o-files\033[0m"
				@/bin/rm -Rf $(DIR_O)
				@make clean --directory ./libft

fclean: clean
				@echo "\033[34mDeliting ft_ls binary\033[0m"
				@/bin/rm -f $(NAME)
				@make fclean --directory ./libft

re:		fclean all
