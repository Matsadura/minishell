/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaoui <zzaoui@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 17:14:33 by zzaoui            #+#    #+#             */
/*   Updated: 2025/06/13 17:14:34 by zzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

/**
 * is_valid_identifier - Checks if a string is a valid identifier
 * @str: The string to check
 * Returns: 1 if valid, 0 otherwise
 */
static int	is_valid_identifier(const char *str)
{
	if (str == NULL || *str == '\0' || ft_isdigit(*str) == 1)
		return (0);
	while (*str)
	{
		if (!ft_isalnum(*str) && *str != '_')
			return (0);
		str++;
	}
	return (1);
}

/**
 * remove_env_var - Removes an environment variable from the env array
 * @arg: The argument containing the variable name to remove
 * @env: The current environment variables
 * Return: 1 if the variable was found and removed, 0 otherwise
 */
static int	remove_env_var(char *arg, char **env)
{
	int	j;
	int	found;

	found = 0;
	j = 0;
	while (env[j])
	{
		if (ft_strncmp(env[j], arg, ft_strlen(arg)) == 0
			&& env[j][ft_strlen(arg)] == '=')
		{
			found = 1;
			while (env[j + 1])
			{
				env[j] = env[j + 1];
				j++;
			}
			env[j] = NULL;
			break ;
		}
		j++;
	}
	return (found);
}

/**
 * unset_builtin - Unsets environment variables
 * @args: The arguments passed to the unset command
 * @env: The current environment variables
 * Return: 0 on success, 1 on failure
 */
int	unset_builtin(char **args, char **env)
{
	int	i;

	if (args == NULL || args[1] == NULL)
		return (0);
	i = 1;
	while (args[i])
	{
		if (is_valid_identifier(args[i]) == 0)
		{
			ft_dprintf(2, "unset: '%s': not a valid identifier\n", args[i]);
			i++;
			continue ;
		}
		remove_env_var(args[i], env);
		i++;
	}
	return (0);
}
