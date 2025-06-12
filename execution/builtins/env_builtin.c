#include "../../includes/execution.h"

/**
 * set_custom_var - Sets or updates a custom environment variable
 * @key: The name of the variable
 * @value: The value of the variable
 * @env: The environment variables array
 */
void	set_custom_var(char *key, char *value, char **env)
{
    int		i;
    char	*new_var;

    if (key == NULL || value == NULL || env == NULL)
        return ;
    new_var = gc_strljoin(key, "=", ft_strlen(key) + 2);
    if (new_var == NULL)
        return ;
    new_var = gc_strljoin(new_var, value, ft_strlen(new_var) + ft_strlen(value) + 1);
    if (new_var == NULL)
        return ;
    i = 0;
    while (env[i])
    {
        if (ft_strncmp(env[i], key, ft_strlen(key)) == 0 && env[i][ft_strlen(key)] == '=')
        {
            env[i] = new_var;
            return ;
        }
        i++;
    }
    env[i] = new_var;
    env[i + 1] = NULL;
}

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
