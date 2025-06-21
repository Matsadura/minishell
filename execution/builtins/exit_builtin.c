/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaoui <zzaoui@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 17:14:40 by zzaoui            #+#    #+#             */
/*   Updated: 2025/06/13 17:14:41 by zzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

/**
 * handle_exit_arg - Handles the argument for the exit command
 * @args: The arguments passed to the exit command
 * Return: 0 if the argument is valid, 1 if it is invalid
 */
static int	handle_exit_arg(char **args)
{
	if (ft_isnumber(args[1]) == 0)
	{
		ft_dprintf(STDERR, "exit\nexit: %s: numeric argument required\n",
			args[1]);
		g_exit_status = 2;
	}
	else
	{
		g_exit_status = ft_atoi(args[1]);
		if (g_exit_status < 0 || g_exit_status > 255 || ft_strlen(args[1]) > 20)
		{
			ft_dprintf(STDERR, "exit\nexit: %s: numeric argument required\n",
				args[1]);
			g_exit_status = 2;
		}
		else
			ft_dprintf(STDOUT, "exit\n");
	}
	return (0);
}

/**
 * exit_builtin - Handles the exit command
 * @args: The arguments passed to the exit command
 * Return: Always returns 0, as this function does not return to the shell
 */
int	exit_builtin(char **args)
{
	if (args[1] == NULL)
	{
		ft_dprintf(STDOUT, "exit\n");
		g_exit_status = 0;
	}
	else if (args[2] != NULL)
		return (ft_dprintf(STDERR, "exit: too many arguments\n"), 1);
	else
		handle_exit_arg(args);
	cleanup_and_exit(g_exit_status);
	return (0);
}
