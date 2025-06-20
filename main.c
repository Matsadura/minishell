/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberkass <aberkass@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 21:25:52 by aberkass          #+#    #+#             */
/*   Updated: 2025/05/02 09:41:30 by aberkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	g_exit_status = 0;

/**
 * main - Entry point of the minishell program.
 * @argc: Argument count.
 * @argv: Argument vector.
 * @env: Environment variables.
 * Returns: Exit status of the program.
 */
int	main(int argc, char **argv, char **env)
{
	char	**env_copy;

	(void)argc;
	(void)argv;
	setup_signals();
	env_copy = create_env(env);
	main_loop(env_copy);
	cleanup_and_exit(g_exit_status);
	return (g_exit_status);
}
