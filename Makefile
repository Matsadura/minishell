CC      = cc
CFLAGS  = -Wall -Werror -Wextra
LDFLAGS = -lreadline
SRC        = main.c
GC_SRC = garbage\ collector/gc_alloc.c garbage\ collector/gc_utils.c
PARS_FILES = parsing/lexer/char_check.c parsing/lexer/lexer_utils.c parsing/lexer/lexer.c \
			parsing/tokeniser/tokeniser_utils.c parsing/tokeniser/tokeniser.c
LIBFT      = libft/libft.a
NAME = minishell

all: $(NAME)

$(NAME): $(SRC) $(PARS_FILES) $(LIBFT)
	$(CC) $(CFLAGS) $(SRC) $(PARS_FILES) $(GC_SRC) $(LIBFT) $(LDFLAGS) -o $@

$(LIBFT):
	make -C libft

clean:
	make -C libft clean

fclean: clean
	rm -f $(NAME)
	make -C libft fclean

re: fclean all

.PHONY: all clean fclean re