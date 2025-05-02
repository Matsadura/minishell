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

#include "minishell.h"

int	main(void)
{
	char	*cmd;

	while (1)
	{
		cmd = readline("minishell$ ");
		if (cmd == NULL)
		{
			printf("exit\n");
			return (EXIT_SUCCESS);
		}
		if (*cmd != 0)
			add_history(cmd);
	}
	return (EXIT_SUCCESS);
}
