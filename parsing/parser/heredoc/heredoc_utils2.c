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
 * handle_heredoc_interrupt - handles interruption during heredoc input
 * @line: the line that was being read
 * return: 0 to stop the heredoc, 1 to continue
 */
static int	handle_heredoc_interrupt(char *line)
{
	g_exit_status = 130;
	setup_signals();
	if (line)
		free(line);
	return (0);
}

/**
 * handle_heredoc_eof - handles EOF in heredoc input
 * @clean_delimiter: the clean delimiter to check against
 * return: 1 on success, 0 on failure
 */
static int	handle_heredoc_eof(char *clean_delimiter)
{
	handle_readline_eof(clean_delimiter);
	setup_signals();
	return (1);
}

/**
 * process_heredoc_loop - processes the heredoc input loop
 * @fd: file descriptor to write to
 * @clean_delimiter: delimiter to check against
 * @ctx: heredoc context containing expansion info and environment
 * return: 1 on success, 0 on failure
 */
static int	process_heredoc_loop(int fd, char *clean_delimiter,
	t_heredoc_ctx *ctx)
{
	char	*line;
	int		result;

	while (1)
	{
		line = readline("> ");
		if (g_exit_status == 999)
			return (handle_heredoc_interrupt(line));
		if (line == NULL)
			return (handle_heredoc_eof(clean_delimiter));
		result = process_single_line(fd, line, clean_delimiter, ctx);
		if (result != 1)
		{
			setup_signals();
			return (result == 2);
		}
	}
}

/**
 * read_heredoc_input - reads heredoc input until delimiter is found
 * @fd: file descriptor to write to
 * @delimiter: original delimiter (potentially quoted)
 * @env: environment variables for expansion
 * return: 1 on success, 0 on failure
 */
int	read_heredoc_input(int fd, char *delimiter, char **env)
{
	char			*clean_delimiter;
	t_heredoc_ctx	ctx;
	int				ret;

	ctx.should_expand = should_expand_heredoc(delimiter);
	ctx.env = env;
	clean_delimiter = remove_quotes(delimiter);
	if (!clean_delimiter)
		return (0);
	setup_heredoc_signals();
	ret = process_heredoc_loop(fd, clean_delimiter, &ctx);
	return (ret);
}
