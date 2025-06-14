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
 * random_name - Generates a random temporary file name.
 * Returns: A string containing the random file name.
 */
static char	*random_name(void)
{
	long	n;
	char	*name;
	char	*full_name;

	n = 1;
	name = ft_ltoa((long) &n);
	while (1)
	{
		if (access(name, F_OK) == -1)
			break ;
		n++;
		free(name);
		name = ft_ltoa((long) &n);
	}
	full_name = gc_strljoin("/tmp/", name, ft_strlen(name) + 5);
	free(name);
	return (full_name);
}

/**
 * create_temp_file - Creates a temporary file for heredoc redirection.
 * Returns: The file descriptor of the created temporary file, or -1 on failure.
 */
char	*create_temp_file(void)
{
	int		fd;
	char	*temp_file;

	temp_file = random_name();
	fd = open(temp_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror(temp_file);
		return (NULL);
	}
	return (temp_file);
}

/**
 * write_heredoc_content - Writes content to a temporary file for heredoc.
 * @temp_file: The name of the temporary file.
 * @delimiter: The delimiter to stop writing.
 * Returns: 0 on success, -1 on failure.
 */
int	write_heredoc_content(char *temp_file, char *del)
{
	int		fd;
	char	*line;

	fd = open(temp_file, O_WRONLY);
	if (fd < 0)
		return (-1);
	ignore_signals();
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
		{
			ft_dprintf(2, "warning: delimited by EOF (wanted `%s')\n", del);
			break ;
		}
		if (ft_strcmp(line, del) == 0)
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
	setup_signals();
	return (close(fd), 0);
}

/**
 * preprocess_heredocs - Preprocesses heredoc redirections in the pipeline.
 * @pipeline: The pipeline containing the commands.
 * Returns: 0 on success, -1 on failure.
 */
int	preprocess_heredocs(t_pipeline *pipeline)
{
	t_cmd		*current;
	t_redirect	*redir;

	current = pipeline->head;
	while (current)
	{
		redir = current->redirections;
		while (redir)
		{
			if (redir->type == HEREDOC)
			{
				if (handle_redir_heredoc(current, redir) < 0)
					return (-1);
			}
			redir = redir->next;
		}
		current = current->next;
	}
	return (0);
}

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
		return (redir_heredoc(command, redir));
	return (0);
}
