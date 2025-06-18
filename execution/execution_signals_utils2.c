/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_signals_utils2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaoui <zzaoui@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 20:11:24 by zzaoui            #+#    #+#             */
/*   Updated: 2025/06/18 20:11:25 by zzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

/**
 * sigint_interactive_handler - Handles the SIGINT signal (Ctrl+C)
 * 		in interactive mode.
 * @sig: The signal number.
 */
void	sigint_interactive_handler(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", STDOUT);
	g_exit_status = 130;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
