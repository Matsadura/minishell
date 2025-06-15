/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_redirection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaoui <zzaoui@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 17:13:59 by zzaoui            #+#    #+#             */
/*   Updated: 2025/06/13 17:14:01 by zzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

/**
 * handle_redir_in - Handles input redirection for a command.
 * @command: The command to which the redirection applies.
 * @redir: The redirection structure containing the type and filename.
 * Returns: 0 on success, -1 on failure.
 */
int	handle_redir_in(t_cmd *command, t_redirect *redir)
{
	command->input_fd = open(redir->filename, O_RDONLY);
	if (command->input_fd < 0)
	{
		perror(redir->filename);
		return (-1);
	}
	if (dup2(command->input_fd, STDIN) < 0)
	{
		perror("dup2");
		close(command->input_fd);
		return (-1);
	}
	close(command->input_fd);
	return (0);
}

/**
 * handle_redir_out - Handles output redirection for a command.
 * @command: The command to which the redirection applies.
 * @redir: The redirection structure containing the type and filename.
 * Returns: 0 on success, -1 on failure.
 */
int	handle_redir_out(t_cmd *command, t_redirect *redir)
{
	command->output_fd = open(redir->filename,
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (command->output_fd < 0)
	{
		perror(redir->filename);
		return (-1);
	}
	if (dup2(command->output_fd, STDOUT) < 0)
	{
		perror("dup2");
		close(command->output_fd);
		return (-1);
	}
	close(command->output_fd);
	return (0);
}

/**
 * handle_redir_append - Handles append redirection for a command.
 * @command: The command to which the redirection applies.
 * @redir: The redirection structure containing the type and filename.
 * Returns: 0 on success, -1 on failure.
 */
int	handle_redir_append(t_cmd *command, t_redirect *redir)
{
	command->output_fd = open(redir->filename,
			O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (command->output_fd < 0)
	{
		perror(redir->filename);
		return (-1);
	}
	if (dup2(command->output_fd, STDOUT) < 0)
	{
		perror("dup2");
		close(command->output_fd);
		return (-1);
	}
	close(command->output_fd);
	return (0);
}

// /**
//  * handle_redir_heredoc - Handles heredoc redirection for a command.
//  * @command: The command to which the redirection applies.
//  * @redir: The redirection structure containing the type and filename.
//  * Returns: 0 on success, -1 on failure.
//  */
// int	handle_redir_heredoc(t_cmd *command, t_redirect *redir)
// {
// 	char	*temp_file;

// 	(void)command;
// 	temp_file = create_temp_file();
// 	if (temp_file == NULL)
// 		return (-1);
// 	if (write_heredoc_content(temp_file, redir->filename) < 0)
// 	{
// 		unlink(temp_file);
// 		return (-1);
// 	}
// 	redir->temp_file = temp_file;
// 	return (0);
// }

/**
 * handle_redirection - Handles all redirections for a command.
 * @command: The command to which the redirections apply.
 * Returns: 0 on success, -1 on failure.
 */
int	handle_redirection(t_cmd *command)
{
	t_redirect	*redir;

	if (command == NULL || command->redirections == NULL)
		return (0);
	redir = command->redirections;
	while (redir)
	{
		if (handle_single_redir(command, redir) < 0)
			return (-1);
		redir = redir->next;
	}
	return (0);
}
