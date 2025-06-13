/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_command.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaoui <zzaoui@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 17:13:28 by zzaoui            #+#    #+#             */
/*   Updated: 2025/06/13 17:13:30 by zzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

/**
 * execute_command - Executes a single command with its arguments
 *          and redirections.
 * @command: The command to execute.
 * @env: The environment variables to pass to the command.
 */
void	execute_command(t_cmd *command, char **env)
{
	char	*executable_path;

	if (command == NULL || command->args == NULL || command->args[0] == NULL)
		exit(1);
	if (handle_redirection(command) < 0)
		exit(1);
	if (is_builtin(command->args[0]) == TRUE)
		exit(execute_builtin(command, env));
	executable_path = find_executable_path(command->args[0], env);
	if (executable_path != NULL)
		command->args[0] = executable_path;
	else
	{
		ft_dprintf(STDERR, "minishell: %s: command not found\n",
			command->args[0]);
		exit(127);
	}
	if (execve(command->args[0], command->args, env) < 0)
	{
		perror(command->args[0]);
		if (errno == ENOENT)
			exit(127);
		exit(126);
	}
}
