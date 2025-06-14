/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_redirection_utils2.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaoui <zzaoui@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 11:00:31 by zzaoui            #+#    #+#             */
/*   Updated: 2025/06/14 11:00:32 by zzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

/**
 * redir_heredoc - Handles heredoc redirection for a command.
 * @command: The command to which the redirection applies.
 * @redir: The redirection structure containing the type and filename.
 * Returns: 0 on success, -1 on failure.
 */
int	redir_heredoc(t_cmd *command, t_redirect *redir)
{
	command->input_fd = open(redir->temp_file, O_RDONLY);
	if (command->input_fd < 0)
	{
		perror(redir->temp_file);
		return (-1);
	}
	if (dup2(command->input_fd, STDIN_FILENO) < 0)
	{
		perror("dup2");
		close(command->input_fd);
		return (-1);
	}
	close(command->input_fd);
	unlink(redir->temp_file);
	return (0);
}
