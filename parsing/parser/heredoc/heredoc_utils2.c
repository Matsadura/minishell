/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaoui <zzaoui@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 06:02:36 by zzaoui            #+#    #+#             */
/*   Updated: 2025/06/17 06:02:37 by zzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/**
 * handle_heredoc_child - Handles the child process for heredoc input.
 * @temp_file: The temporary file created for heredoc input.
 * @redirect: The redirect structure containing heredoc information.
 * @env: Environment variables for expansion.
 * Returns: 0 on success, 130 on SIGINT.
 */
int	handle_heredoc_child(char *temp_file, t_redirect *redirect, char **env)
{
	int	fd;
	int	result;

	fd = open(temp_file, O_WRONLY);
	if (fd < 0)
	{
		perror(temp_file);
		clean_exit(1);
		//exit(1);
	}
	setup_heredoc_signals();
	result = read_heredoc_input(fd, redirect->filename, env);
	close(fd);
	if (result)
		clean_exit(0);
		//exit(0);
	else
		clean_exit(130);
		//exit(130);
	return (1337);
}

/**
 * handle_heredoc_parent - Handles the parent process after heredoc input.
 * @pid: The process ID of the child process.
 * @temp_file: The temporary file created for heredoc input.
 * Returns: 1 on success, 0 on failure.
 */
int	handle_heredoc_parent(pid_t pid, char *temp_file)
{
	int	status;
	int	exit_code;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	{
		exit_code = WEXITSTATUS(status);
		if (exit_code == 130)
		{
			g_exit_status = 130;
			return (unlink(temp_file), 0);
		}
		else if (exit_code != 0)
			return (unlink(temp_file), 0);
	}
	else if (WIFSIGNALED(status))
	{
		g_exit_status = 130;
		return (unlink(temp_file), 0);
	}
	return (1);
}

/**
 * read_heredoc_input - Reads input for heredoc until the delimiter is met.
 * @fd: File descriptor to write the heredoc input to.
 * @delimiter: The delimiter to stop reading input.
 * @env: Environment variables for expansion.
 */
int	read_heredoc_input(int fd, char *delimiter, char **env)
{
	char			*line;
	char			*clean_delimiter;
	t_heredoc_ctx	ctx;
	int				result;

	ctx.should_expand = should_expand_heredoc(delimiter);
	ctx.env = env;
	clean_delimiter = remove_quotes(delimiter);
	if (!clean_delimiter)
		return (0);
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
		{
			handle_readline_eof(clean_delimiter);
			break ;
		}
		result = process_single_line(fd, line, clean_delimiter, &ctx);
		if (result != 1)
			return (result == 2);
	}
	return (1);
}
