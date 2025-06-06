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

t_cmd	*parsing(char *input, char **env, int exit_status)
{
	t_cmd	*cmd_list;
	t_token	*tokens;

	tokens = lex_input(input);
	if (tokens == NULL)
		return (NULL);
	tokens = expander(tokens, env, exit_status);
	tokens = field_splitter(tokens);
	cmd_list = parse_tokens(tokens);
	return (cmd_list);
}

int	main(int argc, char **argv, char **env)
{
	char	*cmd;
	t_cmd	*command_list;

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
		command_list = parsing(cmd, env, 0);
	}
	return (EXIT_SUCCESS);
}
