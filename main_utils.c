/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberkass <aberkass@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 16:25:52 by aberkass          #+#    #+#             */
/*   Updated: 2025/06/20 16:26:30 by aberkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/**
 * get_foldername - generate a prompt based on the cwd
 * return: the formatted prompt
 */
char	*get_foldername(void)
{
	char	cwd[4096];
	char	*prompt;
	char	*tmp;

	tmp = getcwd(cwd, 4096);
	if (tmp == NULL)
		return (gc_strdup("minishell > "));
	if (tmp[1] == '\0')
	{
		return (gc_strdup("➜ /$ "));
	}
	prompt = gc_strjoin("➜ ", tmp + 1);
	return (gc_strjoin(prompt, "$ "));
}

/**
 * get_input - displayed the formatted prompt and reads input line
 * return: the input line
 */
char	*get_input(void)
{
	char	*input;
	char	*prompt;

	prompt = get_foldername();
	input = readline(prompt);
	gc_free(prompt);
	return (input);
}

/**
 * parse_input - Parses the input string into a pipeline structure.
 * @input: The input string to parse.
 * @env: The environment variables to use during parsing.
 * @exit_status: The current exit status of the shell.
 * Returns: A pointer to the parsed pipeline structure, or NULL on failure.
 */
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
	pipeline = parse_tokens(tokens, env);
	return (pipeline);
}

/**
 * handle_input - Handles the input string by parsing it
 * 		and executing the commands.
 * @input: The input string to handle.
 * @env_copy: The environment variables to use during execution.
 */
static void	handle_input(char *input, char **env_copy)
{
	t_pipeline	*pipeline;

	if (*input != 0)
	{
		add_history(input);
		pipeline = parse_input(input, env_copy, g_exit_status);
		if (pipeline == NULL)
		{
			if (g_exit_status == 130)
				return ;
			g_exit_status = 2;
		}
		else
			execute_pipeline(pipeline, env_copy);
	}
}

/**
 * main_loop - The main loop of the shell that reads input
 * 		and processes commands.
 * @env_copy: The environment variables to use during the loop.
 */
void	main_loop(char **env_copy)
{
	char	*input;

	while (1)
	{
		signal(SIGINT, sigint_interactive_handler);
		signal(SIGQUIT, SIG_IGN);
		input = get_input();
		if (input == NULL)
		{
			printf("exit\n");
			free(input);
			cleanup_and_exit(g_exit_status);
		}
		handle_input(input, env_copy);
		free(input);
	}
}
