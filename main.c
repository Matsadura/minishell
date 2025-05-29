/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaoui <zzaoui@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 21:25:52 by aberkass          #+#    #+#             */
/*   Updated: 2025/05/22 17:33:57 by zzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	char	*cmd;
	t_env	*env_list;

	(void) ac;
	(void) av;
	env_list = create_env(env);
	while (1)
	{
		cmd = readline("minishell$ ");
		if (cmd == NULL)
		{
			printf("exit\n");
			return (EXIT_FAILURE);
		}
		if (*cmd != 0)
			add_history(cmd);
		// TO RMV
		if (strcmp(cmd, "env") == 0)
			print_env(env_list);
		if (strcmp(cmd, "pwd") == 0)
			pwd(env_list);
		char *p = getenv("PATH");
		if (strcmp(cmd, "path") == 0)
			printf("%s\n", p);
		if (strcmp(cmd, "export") == 0)
			export_var(&env_list, "TEST_VAR", "TEST_VALUE");
		if (strcmp(cmd, "unset") == 0)
			unset_var(&env_list, "TEST_VAR");
		if (strcmp(cmd, "echo") == 0)
			echo((char *[]){ "echo", "Hello, World!", NULL });

	}
	return (EXIT_SUCCESS);
}
