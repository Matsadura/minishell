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
 * ft_atoll - convert ASCII string to long long integer
 * @str: the string to convert
 * Return: the result long long integer
 */
static long long	ft_atoll(const char *str)
{
	int			i;
	long long	result;
	int			sign;

	sign = 1;
	result = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-')
	{
		sign *= -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (ft_isdigit(str[i]))
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

/**
 * handle_exit_arg - Handles the argument for the exit command
 * @args: The arguments passed to the exit command
 * Return: 0 if the argument is valid, 1 if it is invalid
 */
static int	handle_exit_arg(char **args)
{
	long long	exit_code;

	if (ft_isnumber(args[1]) == 0)
	{
		ft_dprintf(STDERR, "exit\nexit: %s: numeric argument required\n",
			args[1]);
		g_exit_status = 2;
	}
	else
	{
		if (ft_strlen(args[1]) > 19)
		{
			ft_dprintf(STDERR, "exit\nexit: %s: numeric argument required\n",
				args[1]);
			g_exit_status = 2;
			return (0);
		}
		exit_code = ft_atoll(args[1]);
		g_exit_status = (unsigned char)exit_code % 256;
		if (g_exit_status < 0)
			g_exit_status += 256;
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
		ft_dprintf(STDOUT, "exit\n");
	else if (args[2] != NULL)
		return (ft_dprintf(STDERR, "exit: too many arguments\n"), 1);
	else
		handle_exit_arg(args);
	cleanup_and_exit(g_exit_status);
	return (0);
}
