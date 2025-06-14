/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_signals.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaoui <zzaoui@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 14:32:13 by zzaoui            #+#    #+#             */
/*   Updated: 2025/06/14 14:32:14 by zzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

/**
 * sigint_handler - Handles the SIGINT signal (Ctrl+C).
 * @sig: The signal number.
 */
void	sigint_handler(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", STDOUT);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_exit_status = 130;
}

/**
 * sigquit_handler - Handles the SIGQUIT signal (Ctrl+\).
 * @sig: The signal number.
 */
void	sigquit_handler(int sig)
{
	(void)sig;
}

/**
 * sigint_child_handler - Handles the SIGINT signal in child processes.
 */
void	sigint_child_handler(int sig)
{
	(void)sig;
	exit(130);
}

/**
 * sigquit_child_handler - Handles the SIGQUIT signal in child processes.
 * @sig: The signal number.
 */
void	sigquit_child_handler(int sig)
{
	(void)sig;
	ft_dprintf(STDERR, "Quit: (core dumped)\n");
	exit(131);
}
