#include "../../includes/execution.h"

/**
 * pwd_builtin - Prints the current working directory
 * Returns: 0 on success, 1 on failure
 */
int	pwd_builtin(char **env)
{
	char	cwd[4096];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("getcwd");
		return (1);
	}
	set_custom_var("PWD", cwd, env);
	ft_printf("%s\n", cwd);
	return (0);
}
