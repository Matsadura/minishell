/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberkass <aberkass@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 15:00:00 by aberkass          #+#    #+#             */
/*   Updated: 2025/06/15 15:00:00 by aberkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

extern int	g_exit_status;

/**
 * write_heredoc_line - writes a single line to heredoc temp file
 * @fd: file descriptor to write to
 * @line: line to write
 * @should_expand: whether to expand the line
 * @env: environment variables for expansion
 * return: 1 on success, 0 on failure
 */
static int	write_heredoc_line(int fd, char *line, int should_expand, 
	char **env)
{
	char	*expanded_line;

	if (should_expand == 0)
	{
		ft_putendl_fd(line, fd);
		return (1);
	}
	expanded_line = expand_heredoc_line(line, env, g_exit_status);
	
	if (expanded_line == NULL)
	{
		ft_putendl_fd(line, fd);
		return (1);
	}
	ft_putendl_fd(expanded_line, fd);
	return (1);
}

/**
 * read_heredoc_input - reads heredoc input until delimiter is found
 * @fd: file descriptor to write to
 * @delimiter: original delimiter (potentially quoted)
 * @env: environment variables for expansion
 * return: 1 on success, 0 on failure
 */
static int	read_heredoc_input(int fd, char *delimiter, char **env)
{
	char	*line;
	char	*clean_delimiter;
	int		should_expand;

	should_expand = should_expand_heredoc(delimiter);
	clean_delimiter = remove_quotes(delimiter);
	if (!clean_delimiter)
		return (0);
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
		{
			ft_dprintf(2, "warning: delimited by EOF (wanted `%s')\n", 
				clean_delimiter);
			break ;
		}
		if (ft_strcmp(line, clean_delimiter) == 0)
		{
			free(line);
			break ;
		}
		if (write_heredoc_line(fd, line, should_expand, env) == 0)
		{
			free(line);
			return (0);
		}
		free(line);
	}
	setup_signals();
	return (1);
}

/**
 * process_heredoc - processes a heredoc redirection during parsing
 * @redirect: the redirection node to process
 * @env: environment variables for expansion
 * return: 1 on success, 0 on failure
 */
int	process_heredoc(t_redirect *redirect, char **env)
{
	char	*temp_file;
	int		fd;
	int		result;

	temp_file = create_temp_file();
	if (temp_file == NULL)
		return (0);
	fd = open(temp_file, O_WRONLY);
	if (fd < 0)
	{
		perror(temp_file);
		free(temp_file);
		return (0);
	}
	result = read_heredoc_input(fd, redirect->filename, env);
	close(fd);
	if (result == 0)
	{
		unlink(temp_file);
		free(temp_file);
		return (0);
	}
	redirect->temp_file = temp_file;
	printf("temp file : %s\n", redirect->temp_file);
	return (1);
}
