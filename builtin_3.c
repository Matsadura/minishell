/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaoui <zzaoui@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 15:20:06 by zzaoui            #+#    #+#             */
/*   Updated: 2025/05/30 15:20:12 by zzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * exit_builtin - Handles the exit command
 * @args: Array of arguments passed to the exit command
 * @env_list: The head of the environment list
 * @return: Always returns 0
 */
int	exit_builtin(char **args)
{
	int	exit_code;

	if (args[1] != NULL)
	{
		if (ft_isnumber(args[1]) == 1)
		{
			exit_code = ft_atoi(args[1]);
			gc_cleanup();
			exit(exit_code);
		}
		else
		{
			ft_dprintf(2, "exit: %s: numeric argument required\n", args[1]);
			return (1);
		}
	}
	gc_cleanup();
	exit(0);
	return (0);
}
