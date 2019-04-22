NAME = libftprintf.a

FLAGS = -c -Wall -Werror -Wextra

SOURCES = ft_printf.c \
	   processing_functions.c \
	   int_output.c \
	   output_processing_di.c \
	   output_processing_uob.c \
	   output_processing_x.c \
	   char_and_nonstandard_output.c \
	   float_output.c \
	   help_functions_for_int.c \
	   get_float_components.c \
	   get_fraction.c \
	   other_and_bonus.c \
	   get_integer.c \
	   output_processing_f.c \
	   help_functions_for_float.c

DIR_O = objs

DIR_S = srcs

SRCS = $(addprefix $(DIR_S)/,$(SOURCES))

OBJS = $(addprefix $(DIR_O)/,$(SOURCES:.c=.o))

all:	$(NAME)

$(NAME):		text $(OBJS)
				@ar rc $(NAME) $(OBJS)
				@echo "\x1b[32;01mYour libftprintf.a is ready.\x1b[32;01m"

text:
				@echo "\x1b[32;01mCompiling ft_printf...\x1b[32;01m"

$(OBJS):		$(DIR_O)/%.o: $(DIR_S)/%.c includes/ft_printf.h includes/libft.h
				@mkdir -p $(DIR_O)
				@gcc $(FLAGS) -I includes -o $@ $<
clean:
				@echo "\033[34mDeliting ft_print o-files\033[0m"
				@/bin/rm -rf $(DIR_O)

fclean: clean
				@echo "\033[34mDeliting libftprint.a\033[0m"
				@/bin/rm -f $(NAME)

re:		fclean all
