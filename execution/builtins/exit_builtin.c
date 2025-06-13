#include "../../includes/execution.h"

/**
 * exit_builtin - Handles the exit command
 * @args: The arguments passed to the exit command
 * Return: Always returns 0, as this function does not return to the shell
 */
int	exit_builtin(char **args)
{
	int	exit_status;

	if (args[1] == NULL)
	{
		ft_dprintf(STDOUT, "exit\n");
		exit(0);
	}
	else if (args[2] != NULL)
		return (ft_dprintf(STDERR, "exit: too many arguments\n"), 1);
	else if (ft_isnumber(args[1]) == 0)
	{
		ft_dprintf(STDERR, "exit\nexit: %s: numeric argument required\n",
			args[1]);
		exit(2);
	}
	else
	{
		exit_status = ft_atoi(args[1]);
		if (exit_status < 0 || exit_status > 255)
			exit_status = 255;
		ft_dprintf(STDOUT, "exit\n");
		exit(exit_status);
	}
	return (0);
}
