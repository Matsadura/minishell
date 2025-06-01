/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaoui <zzaoui@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 15:08:36 by zzaoui            #+#    #+#             */
/*   Updated: 2025/05/22 15:58:19 by zzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

/**
 * pwd - Prints the current working directory
 * @env: 2D array clone of environ
 */
void	pwd(t_env *env)
{
	char	*dir;
	t_env	*current;

	dir = getcwd(NULL, 0);
	if (dir)
	{
		printf("%s\n", dir);
		return ;
	}
	if (env == NULL)
		return ;
	current = env;
	dir = NULL;
	while (current != NULL)
	{
		dir = get_env(current, "PWD=");
		if (dir != NULL)
		{
			printf("%s\n", dir);
			break ;
		}
		current = current->next;
	}
}

/**
 * print_env - Prints environmental variables to STDOUT
 * @env_list:  The head of the environment list
 */
void	print_env(t_env *env_list)
{
	t_env	*curr;

	curr = env_list;
	while (curr != NULL)
	{
		printf("%s\n", curr->var);
		curr = curr->next;
	}
}

/**
 * export_var - Exports an environment variable
 * @env_list: The head of the environment list
 * @key: The key of the variable to export
 * @value: The value of the variable to export
 */
void	export_var(t_env **env_list, char *key, char *value)
{
	char	*var;
	size_t	var_size;
	t_env	*current;

	if (*env_list == NULL || key == NULL || value == NULL)
		return ;
	var_size = ft_strlen(key) + ft_strlen(value) + 2;
	var = gc_alloc(var_size);
	if (var == NULL)
		return ;
	ft_strlcpy(var, key, var_size);
	ft_strlcat(var, "=", var_size);
	current = *env_list;
	while (current != NULL)
	{
		if (ft_strnstr(current->var, var, ft_strlen(var)) != NULL)
		{
			del_var(env_list, current->var);
			break ;
		}
		current = current->next;
	}
	ft_strlcat(var, value, var_size);
	add_var_back(env_list, add_var(var));
	gc_free(var);
}

/**
 * unset_var - Unsets an environment variable
 * @env_list: The head of the environment list
 * @var: The variable to unset
 */
void	unset_var(t_env **env_list, char *key)
{
	t_env	*current;

	if (*env_list == NULL || key == NULL)
		return ;
	current = *env_list;
	while (current != NULL)
	{
		if (ft_strnstr(current->var, key, ft_strlen(key)) != NULL)
		{
			del_var(env_list, current->var);
			break ;
		}
		current = current->next;
	}
}

/**
 * echo - Prints a string to STDOUT
 * @args: Array of arguments passed to the echo command
 */
void	echo(char **args)
{
	if (sizeof(args) >= 2 && ft_strcmp(args[1], "-n") == 0)
		printf("%s", args[2]);
	else if (sizeof(args) >= 1)
		printf("%s\n", args[1]);
	else
		printf("\n");
}
