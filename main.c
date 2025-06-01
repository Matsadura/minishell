/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberkass <aberkass@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 21:25:52 by aberkass          #+#    #+#             */
/*   Updated: 2025/05/02 09:41:30 by aberkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	print_tokens_list(t_token *list)
{
	char *types[] = {"WORD", "PIPE", "REDIRECT_IN",
		"REDIRECT_OUT", "HERDOC", "APPEND", "S_QUOTE", "D_QUOTE"};
	printf("| %-20s | %s\n", "VALUE", "TYPE");
	printf("-----+----------------------+------------\n");
	while (list != NULL)
	{
		printf("| %-20s | %s\n", list->value, types[list->type]);
		list = list->next;
	}
	printf("\n");
}

int	main(int argc, char **argv, char **env)
{
	char	*cmd;
	t_token	*tokens;
	t_token	*expanded_tokens;
	t_token *splitted;

	(void)argc;
	(void)argv;
	while (1)
	{
		cmd = readline("minishell$ ");
		if (cmd == NULL)
		{
			printf("exit\n");
			return (EXIT_SUCCESS);
		}
		if (*cmd != 0)
			add_history(cmd);
		tokens = lex_input(cmd);
		if (tokens == NULL)
		{
			free(cmd);
			gc_cleanup();
			continue ;
		}
		print_tokens_list(tokens);
		expanded_tokens = expander(tokens, env, 0);
		print_tokens_list(expanded_tokens);
		splitted = field_splitter(expanded_tokens);
		print_tokens_list(splitted);
	}
	return (EXIT_SUCCESS);
}
