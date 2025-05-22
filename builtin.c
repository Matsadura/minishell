/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaoui <zzaoui@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 15:08:36 by zzaoui            #+#    #+#             */
/*   Updated: 2025/05/22 14:08:30 by zzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * pwd - Prints the current working directory
 * @env: 2D array clone of environ
 */
void	pwd(char **env)
{
	char	*dir;
	int		i;

	if (env == NULL)
		return ;
	i = 0;
	dir = NULL;
	while (env[i] != NULL)
	{
		dir = ft_strnstr(env[i], "PWD=", 4);
		if (dir != NULL)
		{
			dir += 4;
			printf("%s\n", dir);
			break ;
		}
		i++;
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
