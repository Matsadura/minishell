/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaoui <zzaoui@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 11:37:49 by zzaoui            #+#    #+#             */
/*   Updated: 2025/06/21 11:37:50 by zzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

/**
 * env_count - Counts the number of environment variables
 * @env: The current environment variables
 * Return: The number of environment variables
 */
int	env_count(char **env)
{
	int	count;

	count = 0;
	while (env && env[count])
		count++;
	return (count);
}

/**
 * env_bubble_sort - Sorts the environment variables in alphabetical order
 * @env: The current environment variables
 * @count: The number of environment variables
 */
void	env_bubble_sort(char **env, int count)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (i < count - 1)
	{
		j = 0;
		while (j < count - i - 1)
		{
			if (ft_strcmp(env[j], env[j + 1]) > 0)
			{
				tmp = env[j];
				env[j] = env[j + 1];
				env[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

/**
 * print_export_var - Prints a single environment variable in export format
 * @env_var: The environment variable to print
 */
void	print_export_var(char *env_var)
{
	char	*eq;

	if (ft_strncmp(env_var, "_=", 2) != 0)
	{
		eq = ft_strchr(env_var, '=');
		if (eq)
		{
			*eq = '\0';
			ft_dprintf(STDOUT, "declare -x %s=\"%s\"\n", env_var, eq + 1);
			*eq = '=';
		}
		else
			ft_dprintf(STDOUT, "declare -x %s\n", env_var);
	}
}

/**
 * export_var_without_value - Handles export of variable without assignment
 * @var_name: The variable name to export
 * @env: The current environment variables
 */
void	export_var_without_value(char *var_name, char **env)
{
	int		i;
	size_t	name_len;

	name_len = ft_strlen(var_name);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], var_name, name_len) == 0
			&& (env[i][name_len] == '=' || env[i][name_len] == '\0'))
			return ;
		i++;
	}
	env[i] = gc_strldup(var_name, name_len);
	env[i + 1] = NULL;
}
