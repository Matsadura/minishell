/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberkass <aberkass@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 21:25:52 by aberkass          #+#    #+#             */
/*   Updated: 2025/05/06 03:15:30 by aberkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * handle_pipe - processes a pipe token and validates next token exists
 * @cntxt: parser context containing the current token
 * return: 1 on success, 0 if syntax error (no command after pipe)
 */
static int	handle_pipe(t_pars_context *cntxt)
{
	consume_token(cntxt);
	if (cntxt->current_token == NULL)
	{
		set_syntax_error(cntxt, "syntax error expected command after pipe");
		return (0);
	}
	return (1);
}

/**
 * link_commands - links a new command to the end of the command list
 * @current: pointer to the current command in the list
 * @cmd: new command to link to the list
 */
static void	link_commands(t_cmd **current, t_cmd *cmd)
{
	(*current)->next = cmd;
	*current = cmd;
}

/**
 * pipeline - parses a pipeline of commands connected by pipes
 * @cntxt: parser context containing token list and current token
 * return: head of the command pipeline or NULL on error
 */
t_cmd	*pipeline_parser(t_pars_context *cntxt)
{
	t_cmd	*head;
	t_cmd	*new_cmd;
	t_cmd	*current;

	head = command(cntxt);
	if (head == NULL)
		return (NULL);
	current = head;
	while (cntxt->current_token && cntxt->current_token->type == PIPE)
	{
		if (handle_pipe(cntxt) == 0)
			return (NULL);
		new_cmd = command(cntxt);
		if (new_cmd == NULL)
			return (NULL);
		link_commands(&current, new_cmd);
	}
	if (cntxt->current_token != NULL)
	{
		set_syntax_error(cntxt, "syntax error unexpect token");
		return (NULL);
	}
	return (head);
}
