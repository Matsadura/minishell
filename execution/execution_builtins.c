#include "../includes/execution.h"

/**
 * is_builtin - Checks if a command is a built-in command
 * @cmd: The command to check
 * Return: TRUE if the command is a built-in command, FALSE otherwise
 */
int	is_builtin(const char *cmd)
{
	if (ft_strcmp(cmd, "cd") == 0 || ft_strcmp(cmd, "echo") == 0
		|| ft_strcmp(cmd, "env") == 0 || ft_strcmp(cmd, "exit") == 0
		|| ft_strcmp(cmd, "export") == 0 || ft_strcmp(cmd, "pwd") == 0
		|| ft_strcmp(cmd, "unset") == 0)
		return (TRUE);
	return (FALSE);
}
/**
 * execute_builtin - Executes a built-in command
 * @pipeline: The pipeline containing the command to execute
 * @env: The environment variables
 * @exit_status: The current exit status of the shell
 * Return: The exit status of the built-in command
 *         Returns -1 if the command is not a built-in command
 */
int	execute_builtin(t_cmd *cmd, char **env, int exit_status)
{
	(void)exit_status;

	if (ft_strcmp(cmd->args[0], "export") == 0)
		return (export_builtin(cmd->args, env));
	else if (ft_strcmp(cmd->args[0], "env") == 0)
		return (env_builtin(env));
	// else if (ft_strcmp(cmd->args[0], "cd") == 0)
	// 	return (cd_builtin(cmd->args, env));
	// else if (ft_strcmp(cmd->args[0], "echo") == 0)
	// 	return (echo_builtin(cmd->args));
	// else if (ft_strcmp(cmd->args[0], "exit") == 0)
	// 	return (exit_builtin(cmd->args, exit_status));
	// else if (ft_strcmp(cmd->args[0], "pwd") == 0)
	// 	return (pwd_builtin());
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		return (unset_builtin(cmd->args, env));
	return (-1);
}
