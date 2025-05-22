/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaoui <zzaoui@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 21:25:52 by aberkass          #+#    #+#             */
/*   Updated: 2025/05/22 16:09:02 by zzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	char	*cmd;
	t_env	*env_list;

	(void) ac;
	(void) av;
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
		env_list = create_env(env);
		if (strcmp(cmd, "env") == 0)
			print_env(env_list);
		if (strcmp(cmd, "pwd") == 0)
			pwd(env_list);
		char *p = getenv("PATH");
		if (strcmp(cmd, "path") == 0)
			printf("%s\n", p);

	}
	return (EXIT_SUCCESS);
}
