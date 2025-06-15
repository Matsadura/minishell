/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaoui <zzaoui@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 17:14:25 by zzaoui            #+#    #+#             */
/*   Updated: 2025/06/13 17:14:26 by zzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

/**
 * is_n_flag - Checks if the argument is the "-n" flag for echo.
 * @arg: The argument to check.
 * Returns: 1 if it is the "-n" flag, 0 otherwise.
 */
static int	is_n_flag(char *arg)
{
	int	i;

	if (arg == NULL || arg[0] != '-')
		return (0);
	i = 1;
	if (arg[i] == '\0')
		return (0);
	while (arg[i] == 'n')
		i++;
	return (arg[i] == '\0');
}

/**
 * print_echo_args - Prints the arguments passed to the echo command.
 * @args: The arguments passed to the echo command.
 * @i: The index to start printing from.
 */
static void	print_echo_args(char **args, int i)
{
	while (args[i])
	{
		if (is_n_flag(args[i]))
		{
			i++;
			continue ;
		}
		ft_printf("%s", args[i]);
		if (args[i + 1])
			ft_printf(" ");
		i++;
	}
}

/**
 * echo_builtin - Prints the arguments passed to the echo command.
 * @args: The arguments passed to the echo command.
 * Returns: 0 on success, 1 on failure.
 */
int	echo_builtin(char **args)
{
	int	i;
	int	newline;

	if (args == NULL || args[0] == NULL)
		return (1);
	newline = 1;
	i = 1;
	if (is_n_flag(args[i]))
	{
		newline = 0;
		i++;
	}
	print_echo_args(args, i);
	if (newline)
		ft_printf("\n");
	return (0);
}
