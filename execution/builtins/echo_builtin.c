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
 * is_valid_n_flag - Checks if the argument is a valid "-n" flag for echo.
 * @arg: The argument to check.
 * Returns: 1 if it is a valid "-n" flag, 0 otherwise.
 */
static int	is_valid_n_flag(char *arg)
{
	int	i;

	if (arg == NULL || arg[0] != '-' || arg[1] == '\0')
		return (0);
	i = 1;
	while (arg[i] != '\0')
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

/**
 * skip_n_flags - Skips all valid -n flags and returns the index
 * @args: The arguments array
 * @start_index: Index to start checking from
 * Returns: Index of first non -n flag argument
 */
static int	skip_n_flags(char **args, int start_index)
{
	int	i;

	i = start_index;
	while (args[i] && is_valid_n_flag(args[i]))
		i++;
	return (i);
}

/**
 * print_echo_args - Prints the arguments passed to the echo command.
 * @args: The arguments passed to the echo command.
 * @start_index: The index to start printing from.
 */
static void	print_echo_args(char **args, int start_index)
{
	int	i;

	i = start_index;
	while (args[i])
	{
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
	int	newline;
	int	start_index;
	int	first_arg_index;

	if (args == NULL || args[0] == NULL)
		return (1);
	newline = 1;
	start_index = 1;
	first_arg_index = skip_n_flags(args, start_index);
	if (first_arg_index > start_index)
		newline = 0;
	print_echo_args(args, first_arg_index);
	if (newline)
		ft_printf("\n");
	return (0);
}
