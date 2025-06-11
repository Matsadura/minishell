#include "../includes/execution.h"

/**
 * create_env - Creates a new environment array by duplicating the existing one.
 * @env: The existing environment variables array.
 * Returns: A new environment array or NULL on failure.
 */
char	**create_env(char **env)
{
	char	**new_env;
	int		i;

	if (env == NULL)
		return (NULL);
	new_env = gc_alloc(sizeof(char *) * (ft_strarrlen(env) + 1));
	if (new_env == NULL)
		return (NULL);
	i = 0;
	while (env[i] != NULL)
	{
		new_env[i] = gc_strldup(env[i], ft_strlen(env[i]));
		if (new_env[i] == NULL)
		{
			gc_free(new_env);
			return (NULL);
		}
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

/**
 * get_env - Retrieves the value of an environment variable.
 * @env: The environment variables array.
 * @name: The name of the environment variable to retrieve.
 * Returns: The value of the environment variable or NULL if not found.
 */
char	*get_env(char **env, const char *name)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], name, ft_strlen(name)) == 0
			&& env[i][ft_strlen(name)] == '=')
			return (env[i] + ft_strlen(name) + 1);
		i++;
	}
	return (NULL);
}

/**
 * get_path_env - Retrieves the PATH environment variable
 * 		and splits it into an array.
 * @env: The environment variables array.
 * Returns: An array of paths or NULL if PATH is not found
 * 		or memory allocation fails.
 */
char	**get_path_env(char **env)
{
	char	*path_env;
	char	**paths;

	path_env = get_env(env, "PATH");
	if (path_env == NULL)
		return (NULL);
	paths = gc_split(path_env, ':');
	if (paths == NULL)
		return (NULL);
	return (paths);
}

/**
 * find_executable_path - Searches for the executable path of a command.
 * @cmd: The command to search for.
 * @env: The environment variables array.
 * Returns: The full path to the executable if found, or NULL if not found.
 */
char	*find_executable_path(char *cmd, char **env)
{
	char	*path_env;
	char	*full_path;
	char	**paths;
	int		i;

	if (cmd == NULL || cmd[0] == '\0')
		return (NULL);
	if (ft_strchr(cmd, '/') != NULL)
		return (gc_strldup(cmd, ft_strlen(cmd)));
	path_env = get_env(env, "PATH");
	if (path_env == NULL)
		return (NULL);
	paths = gc_split(path_env, ':');
	if (paths == NULL)
		return (NULL);
	i = 0;
	while (paths[i] != NULL)
	{
		full_path = gc_strljoin(paths[i], "/", 1024);
		full_path = gc_strljoin(full_path, cmd, 1024);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		i++;
	}
	return (NULL);
}
