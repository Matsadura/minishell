/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberkass <aberkass@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 21:25:52 by aberkass          #+#    #+#             */
/*   Updated: 2025/05/06 03:15:30 by aberkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * init_parser_context - initialises the parser context structure
 * @cntx: pointer to the parser context to initialise
 * @tokens: linked list of tokens to be parsed
 */
static void	init_parser_context(t_pars_context *cntx, t_token *tokens)
{
	cntx->token_list = tokens;
	cntx->current_token = tokens;
	cntx->has_syntax_error = 0;
	cntx->error_message = NULL;
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
 * parse_tokens - main parsing function that converts tokens into command list
 * @tokens: linked list of tokens to be parsed into commands
 * return: parsed command list or NULL if syntax error occurs
 */
t_pipeline	*parse_tokens(t_token *tokens)
{
	t_cmd			*command_list;
	t_pars_context	cntx;

	init_parser_context(&cntx, tokens);
	command_list = pipeline_parser(&cntx);
	if (cntx.has_syntax_error == 1)
	{
		if (cntx.error_message != NULL)
		{
			ft_dprintf(2, "minishell: %s\n", cntx.error_message);
			gc_free(cntx.error_message);
		}
		return (NULL);
	}
	return (get_pipeline(command_list));
}
