/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberkass <aberkass@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 21:25:52 by aberkass          #+#    #+#             */
/*   Updated: 2025/05/06 03:15:30 by aberkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * init_cmd_node - creates and initialises a new command node
 * return: pointer to initialised command node or NULL on allocation failure
 */
static t_cmd	*init_cmd_node(void)
{
	t_cmd	*cmd;

	cmd = gc_alloc(sizeof(t_cmd));
	if (cmd == NULL)
		return (NULL);
	cmd->args = NULL;
	cmd->redirections = NULL;
	cmd->input_fd = -1;
	cmd->output_fd = -1;
	cmd->pid = -1;
	cmd->next = NULL;
	return (cmd);
}

/**
 * is_cmd_token - checks if current token is part of a command
 * @cntx: parser context containing the current token
 * return: 1 if token is a redirection or word 0 otherwise
 */
static int	is_valid_cmd_token(t_pars_context *cntx)
{
	return (is_redirection(cntx->current_token->type)
		|| cntx->current_token->type == WORD);
}

/**
 * process_cmd_token - processes a single command token (redirection or word)
 * @cntx: parser context containing the current token
 * @cmd: command node to add the token to
 * @count: pointer to argument count for word tokens
 * return: 1 on success, 0 on failure
 */
static int	process_cmd_token(t_pars_context *cntx, t_cmd *cmd, int *count)
{
	if (is_redirection(cntx->current_token->type))
	{
		if (parse_redirect(cntx, &cmd->redirections) == 0)
			return (0);
	}
	else if (cntx->current_token->type == WORD)
	{
		if (parse_word(cntx, &cmd->args, count) == 0)
			return (0);
	}
	return (1);
}

/**
 * has_cmd_content - checks if a command has any content (args or redirections)
 * @cmd: command node to check
 * @args_count: number of arguments in the command
 * return: 1 if command has content, 0 if empty
 */
static int	has_cmd_content(t_cmd *cmd, int args_count)
{
	return (cmd->redirections != NULL || args_count > 0);
}

/**
 * command - parses a complete command with its arguments and redirections
 * @cntx: parser context containing the token stream
 * return: parsed command node or NULL on error
 */
t_cmd	*command(t_pars_context *cntx)
{
	t_cmd	*cmd_node;
	int		args_count;

	args_count = 0;
	cmd_node = init_cmd_node();
	if (cmd_node == NULL)
		return (NULL);
	while (cntx->current_token != NULL && is_valid_cmd_token(cntx))
	{
		if (process_cmd_token(cntx, cmd_node, &args_count) == 0)
			return (NULL);
	}
	if (has_cmd_content(cmd_node, args_count) == 0)
	{
		set_syntax_error(cntx, "syntax error empty command");
		return (NULL);
	}
	return (cmd_node);
}
