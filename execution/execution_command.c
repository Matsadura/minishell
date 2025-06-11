#include "../includes/execution.h"

/**
 * execute_command - Executes a single command with its arguments
 *          and redirections.
 * @command: The command to execute.
 * @env: The environment variables to pass to the command.
 */
void	execute_command(t_cmd *command, char **env)
{
	if (command == NULL || command->args == NULL || command->args[0] == NULL)
		exit(EXIT_FAILURE);
	if (handle_redirection(command) < 0)
		exit(EXIT_FAILURE);
	if (execve(command->args[0], command->args, env) < 0)
	{
		perror(command->args[0]);
		if (errno == ENOENT)
			exit(127);
		else
			exit(126);
	}
}
