#include "../../includes/execution.h"

/**
 * env_builtin - Prints the current environment variables
 * @env: The environment variables
 * Return: 0 on success, 1 on failure
 */
int	env_builtin(char **env)
{
	int	i;

	if (env == NULL)
	{
		ft_dprintf(STDERR, "env: No environment variables found\n");
		return (1);
	}
	i = 0;
	while (env[i])
	{
		ft_dprintf(STDOUT, "%s\n", env[i]);
		i++;
	}
	return (0);
}
