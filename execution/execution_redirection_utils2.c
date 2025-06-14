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

/**
 * save_and_redirect_builtin - Saves original FDs
 * 		and applies redirections for builtins
 * @command: The command with redirections
 * @saved_stdin: Pointer to store original stdin
 * @saved_stdout: Pointer to store original stdout
 * Returns: 0 on success, -1 on failure
 */
int	save_and_redirect_builtin(t_cmd *command, int *saved_stdin,
	int *saved_stdout)
{
	*saved_stdin = dup(STDIN_FILENO);
	*saved_stdout = dup(STDOUT_FILENO);
	if (*saved_stdin < 0 || *saved_stdout < 0)
	{
		perror("dup");
		return (-1);
	}
	if (handle_redirection(command) < 0)
	{
		close(*saved_stdin);
		close(*saved_stdout);
		return (-1);
	}
	return (0);
}

/**
 * restore_builtin_fds - Restores original file descriptors
 * 		after builtin execution
 * @saved_stdin: Original stdin file descriptor
 * @saved_stdout: Original stdout file descriptor
 */
void	restore_builtin_fds(int saved_stdin, int saved_stdout)
{
	if (saved_stdin >= 0)
	{
		dup2(saved_stdin, STDIN_FILENO);
		close(saved_stdin);
	}
	if (saved_stdout >= 0)
	{
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdout);
	}
}
