CC = cc
CFLAGS = -Wall -Werror -Wextra 
SRC = main.c builtin.c env_func.c
GSRC = garbage_collector/gc_alloc.c garbage_collector/gc_utils.c
NAME = minishell
LIBFT = libft/libft.a

all: $(NAME)

$(NAME): $(SRC) $(LIBFT)
	$(CC) $(CFLAGS) $(SRC) $(GSRC) $(LIBFT) -lreadline -o $(NAME)

$(LIBFT):
	make -C libft

clean:
	make -C libft clean

fclean: clean
	rm -f $(NAME)
	make -C libft fclean

re: fclean all

.PHONY: clean fclean all re
