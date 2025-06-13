#include "../../includes/execution.h"

/**
 * get_target_directory - Determines the target directory for the cd command
 * @args: The arguments passed to the cd command
 * @env: The current environment variables
 * Return: The target directory as a string, or NULL on failure
 */
static char	*get_target_directory(char **args, char **env)
{
	char	*target;

	if (args[1] == NULL || ft_strcmp(args[1], "~") == 0)
	{
		target = get_env(env, "HOME");
		if (target == NULL)
		{
			ft_dprintf(STDERR, "cd: HOME not set\n");
			return (NULL);
		}
	}
	else if (ft_strcmp(args[1], "-") == 0)
	{
		target = get_env(env, "OLDPWD");
		if (target == NULL)
		{
			ft_dprintf(STDERR, "cd: OLDPWD not set\n");
			return (NULL);
		}
	}
	else
		target = args[1];
	return (target);
}

/**
 * cd_builtin - Changes the current working directory
 * @args: The arguments passed to the cd command
 * @env: The current environment variables
 * Return: 0 on success, 1 on failure
 */
int	cd_builtin(char **args, char **env)
{
	char	*target;
	char	oldpwd[4096];
	char	pwd[4096];
	int		ret;

	target = get_target_directory(args, env);
	if (target == NULL)
		return (1);
	getcwd(oldpwd, sizeof(oldpwd));
	ret = chdir(target);
	if (ret == -1)
	{
		ft_dprintf(STDERR, "cd: %s: %s\n", target, strerror(errno));
		return (1);
	}
	set_custom_var("OLDPWD", oldpwd, env);
	getcwd(pwd, sizeof(pwd));
	set_custom_var("PWD", pwd, env);
	return (0);
}
