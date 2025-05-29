/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaoui <zzaoui@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:11:20 by zzaoui            #+#    #+#             */
/*   Updated: 2025/05/22 14:20:56 by zzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * add_var - Creates a new variable node
 * @var: The variable
 * Return: The newly created node
 */
t_env	*add_var(char *var)
{
	t_env	*new;

	if (var == NULL)
		return (NULL);
	new = gc_alloc(sizeof(t_env));
	if (new == NULL)
		return (NULL);
	new->var = var;
	new->next = NULL;
	return (new);
}

/**
 * add_var_back - Add variable mode to the end of the env list
 * @lst: Head of the list
 * @var: Variable node
 */
void	add_var_back(t_env **lst, t_env *var)
{
	t_env	*current;

	if (var == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = var;
		return ;
	}
	current = *lst;
	while (current->next)
		current = current->next;
	current->next = var;
}

/**
 * del_var - Delete a variable node from the list
 * @lst: Head of the list
 * @var: Variable to delete
 */
void	del_var(t_env **lst, char *var)
{
	t_env	*current;
	t_env	*prev;

	if (lst == NULL || *lst == NULL)
		return ;
	current = *lst;
	prev = NULL;
	while (current != NULL)
	{
		if (ft_strcmp(current->var, var) == 0)
		{
			if (prev == NULL)
				*lst = current->next;
			else
				prev->next = current->next;
			return ;
		}
		prev = current;
		current = current->next;
	}
}

/**
 * create_env - Duplicate the environment in a linked list
 * @env: 2D array contains the environmental variables
 * Return: The head of the linked list
 */
t_env	*create_env(char **env)
{
	t_env	*env_list;
	t_env	*node;
	int		i;

	env_list = NULL;
	i = 0;
	while (env[i] != NULL)
	{
		node = add_var(env[i]);
		add_var_back(&env_list, node);
		i++;
	}
	return (env_list);
}

/**
 * get_env - Get the value of an environment variable
 * @env_list: The head of the environment list
 * @var: The variable to search for
 * Return: The value of the variable or NULL if not found
 */
char	*get_env(t_env *env_list, const char *var)
{
	t_env	*current;
	size_t	var_len;

	if (env_list == NULL || var == NULL)
		return (NULL);
	var_len = ft_strlen(var);
	current = env_list;
	while (current != NULL)
	{
		if (ft_strncmp(current->var, var, var_len) == 0
			&& current->var[var_len] == '=')
			return (current->var + var_len + 1);
		current = current->next;
	}
	return (NULL);
}
