/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaoui <zzaoui@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:11:20 by zzaoui            #+#    #+#             */
/*   Updated: 2025/05/21 17:11:23 by zzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/**
 * 
 */
t_env   *add_var(char *var)
{
    t_env   *new;

    new = (t_env *)malloc(sizeof(t_env));
    if (new == NULL)
		return (NULL);
	new->var = var;
	new->next = NULL;
	return (new);
}

/**
 * 
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
 * 
 */
t_env   *create_env(char **env)
{
    t_env   *env_list;
	t_env	*node;
    int     i;

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
 * 
 */
void	print_list(t_env *env_list)
{
	t_env *curr;

	curr = env_list;
	while (curr != NULL)
	{
		printf("%s\n", curr->var);
		curr = curr->next;
	}
}
