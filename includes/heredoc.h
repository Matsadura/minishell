/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h.                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberkass <aberkass@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 15:00:00 by aberkass          #+#    #+#             */
/*   Updated: 2025/06/16 22:33:20 by aberkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H

# include "minishell.h"

typedef struct s_heredoc_ctx
{
	int		should_expand;
	char	**env;
	int		exit_status;
}	t_heredoc_ctx;

typedef struct s_expand_data
{
	char	**env;
	int		exit_status;
}	t_expand_data;

//heredoc handler main function
int		process_heredoc(t_redirect *redirect, char **env);

//heredoc expander
char	*expand_heredoc_line(char *line, char **env, int exit_status);

//heredoc utils
char	*create_temp_file(void);
char	*remove_quotes(char *delimiter);
int		should_expand_heredoc(char *delimiter);
void	handle_readline_eof(char *clean_delimiter);

#endif