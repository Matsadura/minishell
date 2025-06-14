CC      = cc

CFLAGS  = -Wall -Werror -Wextra -ggdb

LDFLAGS = -lreadline

SRC        = main.c

GC_SRC = garbage_collector/gc_alloc.c garbage_collector/gc_utils.c garbage_collector/gc_strings.c \
          garbage_collector/gc_split.c

LEXER_FILES = parsing/lexer/lexer.c parsing/lexer/char_utils.c parsing/lexer/lexer_handlers.c

TOKENISER_FILES = parsing/tokeniser/tokeniser.c parsing/tokeniser/token_utils.c

EXPANDER_FILES = parsing/expander/expander.c parsing/expander/expansion_utils.c \
				parsing/expander/token_expansion.c parsing/expander/quote_processing.c \
				parsing/expander/variable_expansion.c

FIELDS_FILES = parsing/expander/fields/field_splitter.c parsing/expander/fields/field_list_utils.c \
			parsing/expander/fields/field_checker.c parsing/expander/fields/string_splitter.c \
			parsing/expander/fields/ambiguous_redirect_handler.c

PARSER_FILES = parsing/parser/parse_command.c parsing/parser/parse_pipeline.c parsing/parser/parse_redirection.c \
			parsing/parser/parse_word.c parsing/parser/parser_utils.c parsing/parser/parser.c

PARSING_FILES = $(LEXER_FILES) $(TOKENISER_FILES) $(EXPANDER_FILES) $(FIELDS_FILES) $(PARSER_FILES)

EXECUTION_FILES = execution/execution_command.c execution/execution_redirection.c \
				execution/execution_pipe.c execution/execution_path.c execution/execution_builtins.c \
				execution/builtins/env_builtin.c execution/builtins/export_builtin.c execution/builtins/unset_builtin.c \
				execution/builtins/pwd_builtin.c execution/builtins/echo_builtin.c execution/builtins/cd_builtin.c \
				execution/builtins/exit_builtin.c execution/execution_pipe_utils.c execution/execution_redirection_utils.c \
				execution/execution_redirection_utils2.c

LIBFT      = libft/libft.a

NAME = minishell

all: $(NAME)

$(NAME): $(SRC) $(PARSING_FILES) $(EXECUTION_FILES) $(LIBFT)
	$(CC) $(CFLAGS) $(SRC) $(PARSING_FILES) $(EXECUTION_FILES) $(GC_SRC) $(LIBFT) $(LDFLAGS) -o $@

$(LIBFT):
	make -C libft

clean:
	make -C libft clean

fclean: clean
	rm -f $(NAME)
	make -C libft fclean

re: fclean all

.PHONY: all clean fclean re