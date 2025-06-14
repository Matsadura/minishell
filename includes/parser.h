/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberkass <aberkass@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 21:25:52 by aberkass          #+#    #+#             */
/*   Updated: 2025/05/06 03:15:30 by aberkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

typedef struct s_pars_context
{
	t_token	*token_list;
	t_token	*current_token;
	int		has_syntax_error;
	char	*error_message;
}	t_pars_context;

typedef struct s_redirect
{
	t_token_type		type;
	char				*filename;
	int					fd;
	char				*temp_file;
	struct s_redirect	*next;
}	t_redirect;

typedef struct s_cmd
{
	char			**args;
	t_redirect		*redirections;
	int				input_fd;
	int				output_fd;
	pid_t			pid;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_pipeline
{
	t_cmd	*head;
	int		cmd_count;
}	t_pipeline;

t_pipeline	*parse_tokens(t_token *tokens);

t_cmd		*pipeline_parser(t_pars_context *cntxt);
t_cmd		*command(t_pars_context *cntxt);

int			is_redirection(t_token_type type);
void		set_syntax_error(t_pars_context *cntxt, char *message);
void		consume_token(t_pars_context *cntxt);

int			parse_word(t_pars_context *cntxt, char ***args, int *arg_count);
int			parse_redirect(t_pars_context *cntxt, t_redirect **redirections);

#endif