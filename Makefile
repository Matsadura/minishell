NAME 	= minishell
CC      = cc
CFLAGS  = -Wall -Werror -Wextra -ggdb
LDFLAGS = -lreadline

GC_SRC = \
		garbage_collector/gc_alloc.c \
		garbage_collector/gc_utils.c \
		garbage_collector/gc_strings.c \
		garbage_collector/gc_itoa.c \
        garbage_collector/gc_split.c

LEXER_SRC = \
		parsing/lexer/lexer.c \
		parsing/lexer/char_utils.c \
		parsing/lexer/lexer_handlers.c

TOKENISER_SRC = \
		parsing/tokeniser/tokeniser.c \
		parsing/tokeniser/token_utils.c

EXPANDER_SRC = \
		parsing/expander/expander.c \
		parsing/expander/expansion_char_utils.c \
		parsing/expander/token_expansion.c \
		parsing/expander/quote_processing.c \
		parsing/expander/variable_expansion.c \
		parsing/expander/expansion_utils.c

FIELDS_SRC = \
		parsing/expander/fields/field_splitter.c \
		parsing/expander/fields/field_list_utils.c \
		parsing/expander/fields/field_checker.c \
		parsing/expander/fields/field_splitter_ifs.c \
		parsing/expander/fields/field_splitter_ifs_utils.c \
		parsing/expander/fields/ambiguous_redirect_handler.c

PARSER_SRC = \
		parsing/parser/parse_command.c \
		parsing/parser/parse_pipeline.c \
		parsing/parser/parse_redirection.c \
		parsing/parser/parse_word.c \
		parsing/parser/parser_utils.c \
		parsing/parser/parser.c
	
HEREDOC_SRC = \
		parsing/parser/heredoc/heredoc_expander.c \
		parsing/parser/heredoc/heredoc_parser.c \
		parsing/parser/heredoc/heredoc_utils.c \
		parsing/parser/heredoc/heredoc_utils2.c

PARSING_SRC = $(LEXER_SRC) $(TOKENISER_SRC) $(EXPANDER_SRC) $(FIELDS_SRC) $(PARSER_SRC) $(HEREDOC_SRC)

BUILTINS_SRC = \
		execution/builtins/env_builtin.c \
		execution/builtins/export_builtin.c \
		execution/builtins/unset_builtin.c \
		execution/builtins/pwd_builtin.c \
		execution/builtins/echo_builtin.c \
		execution/builtins/cd_builtin.c \
		execution/builtins/exit_builtin.c

EXECUTION_SRC = \
		execution/execution_command.c \
		execution/execution_utils.c \
		execution/execution_builtins.c\
		execution/execution_pipe.c \
		execution/execution_path.c \
		execution/execution_pipe_utils.c \
 		execution/execution_redirection_utils.c \
		execution/execution_redirection_utils2.c \
		execution/execution_redirection.c\
		execution/execution_signals.c \
		execution/execution_signals_utils.c \
		execution/execution_signals_utils2.c \
		execution/execution_cleanup.c

SRC = main.c main_utils.c $(PARSING_SRC) $(BUILTINS_SRC) $(EXECUTION_SRC) $(GC_SRC)

OBJ_DIR = objects

OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

LIBFT      = libft/libft.a

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME) $(LDFLAGS)

$(LIBFT):
	make -C libft

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

#$(OBJ_DIR):
#	@mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)
	make -C libft clean

fclean: clean
	rm -f $(NAME)
	make -C libft fclean

re: fclean all

.PHONY: all clean fclean re