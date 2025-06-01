CC      = cc

CFLAGS  = -Wall -Werror -Wextra

LDFLAGS = -lreadline

SRC        = main.c

GC_SRC = garbage_collector/gc_alloc.c garbage_collector/gc_utils.c garbage_collector/gc_strings.c

LEXER_FILES = parsing/lexer/lexer.c parsing/lexer/char_check.c parsing/lexer/lexer_utils.c

TOKENISER_FILES = parsing/tokeniser/tokeniser.c parsing/tokeniser/tokeniser_utils.c

EXPANDER_FILES = parsing/expander/expander.c parsing/expander/expander_utils.c \
				parsing/expander/expander_helpers.c parsing/expander/process_quotes.c \
				parsing/expander/variable_expansion.c

FIELDS_FILES = parsing/expander/fields/fields_splitter.c parsing/expander/fields/fields_list.c \
			parsing/expander/fields/fields_splitter_utils.c parsing/expander/fields/ft_split_by_space.c 

PARS_FILES = $(LEXER_FILES) $(TOKENISER_FILES) $(EXPANDER_FILES) $(FIELDS_FILES)

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