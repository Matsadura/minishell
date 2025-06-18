/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_redirection_utils.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaoui <zzaoui@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 20:32:47 by zzaoui            #+#    #+#             */
/*   Updated: 2025/06/13 20:32:48 by zzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

/**
 * handle_signle_redir - Handles a single redirection for a command.
 * @command: The command to which the redirection applies.
 * @redir: The redirection structure containing the type and filename.
 * Returns: 0 on success, -1 on failure.
 */
int	handle_single_redir(t_cmd *command, t_redirect *redir)
{
	if (redir->type == REDIRECT_IN)
		return (handle_redir_in(command, redir));
	else if (redir->type == REDIRECT_OUT)
		return (handle_redir_out(command, redir));
	else if (redir->type == APPEND)
		return (handle_redir_append(command, redir));
	else if (redir->type == HEREDOC)
		return (handle_redir_heredoc(command, redir));
	return (0);
}
