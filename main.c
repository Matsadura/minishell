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

static t_pipeline	*parse_input(char *input, char **env, int exit_status)
{
	t_pipeline	*pipeline;
	t_token		*tokens;

	tokens = lex_input(input);
	if (tokens == NULL)
		return (NULL);
	tokens = expander(tokens, env, exit_status);
	if (tokens == NULL)
		return (NULL);
	pipeline = parse_tokens(tokens);
	return (pipeline);
}

int g_exit_status = 0;

int	main(int argc, char **argv, char **env)
{
	char		*input;
	char		**env_copy;
	t_pipeline	*pipeline;

	(void)argc;
	(void)argv;
	env_copy = create_env(env);
	while (1)
	{
		input = readline("minishell$ ");
		if (input == NULL)
		{
			printf("exit\n");
			free(input);
			gc_cleanup();
			rl_clear_history();
			return (g_exit_status);
		}
		if (*input != 0)
		{
			add_history(input);
			pipeline = parse_input(input, env_copy, g_exit_status);
			if (pipeline == NULL)
				g_exit_status = 258;
			else
				//printf("cmd count: %d\n", pipeline->cmd_count);
				execute_pipeline(pipeline, env_copy);
		}
		free(input);
	}
	gc_cleanup();
	rl_clear_history();
	return (g_exit_status);
}
