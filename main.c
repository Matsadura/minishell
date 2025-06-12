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
//to do:
// handle ambigious redirect
void	print_tokens_list(t_token *list)
{
	char *types[] = {"WORD", "PIPE", "REDIRECT_IN",
		"REDIRECT_OUT", "HEREDOC", "APPEND", "S_QUOTE", "D_QUOTE"};
	printf("| %-20s | %s\n", "VALUE", "TYPE");
	printf("-----+----------------------+------------\n");
	while (list != NULL)
	{
		printf("| [%s] | %s\n", list->value, types[list->type]);
		list = list->next;
	}
	printf("\n");
}

static t_pipeline	*parse_input(char *input, char **env, int exit_status)
{
	t_pipeline	*pipeline;
	t_token		*tokens;

	tokens = lex_input(input);
	if (tokens != NULL)
		print_tokens_list(tokens);
	if (tokens == NULL)
		return (NULL);
	tokens = expander(tokens, env, exit_status);
	print_tokens_list(tokens);
	tokens = field_splitter(tokens);
	print_tokens_list(tokens);
	pipeline = parse_tokens(tokens);
	return (pipeline);
}

int	main(int argc, char **argv, char **env)
{
	char		*input;
	// t_pipeline	*pipeline;
	int			exit_status;

	(void)argc;
	(void)argv;
	exit_status = 0;
	while (1)
	{
		input = readline("minishell$ ");
		if (input == NULL)
		{
			printf("exit\n");
			return (EXIT_SUCCESS);
		}
		if (*input != 0)
		{
			add_history(input);
			/*pipeline =*/ parse_input(input, env, exit_status);
		}
		free(input);
		gc_cleanup();
	}
	return (EXIT_SUCCESS);
}
