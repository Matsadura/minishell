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
		dir = ft_strnstr(current->var, "PWD=", 4);
		if (dir != NULL)
		{
			dir += 4;
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
