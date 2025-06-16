/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberkass <aberkass@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 21:25:52 by aberkass          #+#    #+#             */
/*   Updated: 2025/06/15 15:00:00 by aberkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * init_parser_context - initialises the parser context structure
 * @cntxt: pointer to the parser context to initialise
 * @tokens: linked list of tokens to be parsed
 */
static void	init_parser_context(t_pars_context *cntxt, t_token *tokens)
{
	cntxt->token_list = tokens;
	cntxt->current_token = tokens;
	cntxt->has_syntax_error = 0;
	cntxt->error_message = NULL;
}

/**
 * get_pipeline - creates a pipeline structure from a command list
 * @cmd_list: linked list of commands to wrap in a pipeline
 * return: pointer to pipeline structure or NULL on allocation failure
 */
static t_pipeline	*get_pipeline(t_cmd *cmd_list)
{
	int			cmd_count;
	t_cmd		*current;
	t_pipeline	*pipeline;

	cmd_count = 0;
	current = cmd_list;
	while (current != NULL)
	{
		cmd_count++;
		current = current->next;
	}
	pipeline = gc_alloc(sizeof(t_pipeline));
	if (pipeline == NULL)
		return (NULL);
	pipeline->head = cmd_list;
	pipeline->cmd_count = cmd_count;
	return (pipeline);
}

/**
 * handle_parser_error - handles parser errors and cleanup
 * @cntxt: parser context containing error information
 */
static void	handle_parser_error(t_pars_context *cntxt)
{
	if (cntxt->error_message != NULL)
	{
		ft_dprintf(2, "minishell: %s\n", cntxt->error_message);
		gc_free(cntxt->error_message);
	}
}

/**
 * parse_tokens - main parsing function that converts tokens into command list
 * @tokens: linked list of tokens to be parsed into commands
 * @env: environment variables for heredoc expansion
 * return: parsed command list or NULL if syntax error occurs
 */
t_pipeline	*parse_tokens(t_token *tokens, char **env)
{
	t_cmd			*command_list;
	t_pars_context	cntxt;

	init_parser_context(&cntxt, tokens);
	command_list = pipeline_parser(&cntxt, env);
	if (cntxt.has_syntax_error == 1)
	{
		handle_parser_error(&cntxt);
		return (NULL);
	}
	return (get_pipeline(command_list));
}
