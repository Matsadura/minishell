#include "../../includes/execution.h"

/**
 * join_env_var - Joins a name and value into an environment variable string
 * @name: The name of the environment variable
 * @value: The value of the environment variable
 * Return: A newly allocated string in the format "NAME=VALUE" or NULL on failure
 */
static char	*join_env_var(char *name, char *value)
{
	char	*env_var;

	if (name == NULL || value == NULL)
		return (NULL);
	env_var = gc_strljoin(name, "=", 2 + ft_strlen(name));
	if (env_var == NULL)
		return (NULL);
	env_var = gc_strljoin(env_var, value,
			ft_strlen(env_var) + 1 + ft_strlen(value) + 1);
	return (env_var);
}

/**
 * set_env_var - Sets or updates an environment variable
 * @arg: The argument containing the variable name
 * 		and value in the format "NAME=VALUE"
 * @env: The current environment variables
 */
static void	set_env_var(char *arg, char **env)
{
	char	*eq_pos;
	char	*name;
	char	*value;
	int		i;
	size_t	name_len;

	eq_pos = ft_strchr(arg, '=');
	if (eq_pos == NULL)
		return ;
	name_len = eq_pos - arg;
	name = gc_substr(arg, 0, name_len);
	value = eq_pos + 1;
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], name, name_len) == 0 && env[i][name_len] == '=')
		{
			env[i] = join_env_var(name, value);
			return ;
		}
		i++;
	}
	env[i] = join_env_var(name, value);
	env[i + 1] = NULL;
}

/**
 * export_builtin - Exports environment variables
 * @args: The arguments passed to the export command
 * @env: The current environment variables
 * Return: 0 on success, 1 on failure
 */
int	export_builtin(char **args, char **env)
{
	int	i;
	int	ret;

	if (args == NULL || args[1] == NULL)
	{
		ft_dprintf(STDERR, "export: No arguments provided\n");
		return (1);
	}
	i = 1;
	ret = 0;
	while (args[i])
	{
		if (ft_strchr(args[i], '=') == NULL)
		{
			ft_dprintf(STDERR, "export: '%s': not a valid identifier\n",
				args[i]);
			ret = 1;
		}
		else
			set_env_var(args[i], env);
		i++;
	}
	return (ret);
}
