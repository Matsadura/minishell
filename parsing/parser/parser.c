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
 * parse_tokens - main parsing function that converts tokens into command list
 * @tokens: linked list of tokens to be parsed into commands
 * return: parsed command list or NULL if syntax error occurs
 */
t_cmd	*parse_tokens(t_token *tokens)
{
	t_cmd			*command_list;
	t_pars_context	cntx;

	init_parser_context(&cntx, tokens);
	command_list = pipeline(&cntx);
	if (cntx.has_syntax_error == 1)
	{
		if (cntx.error_message != NULL)
		{
			ft_dprintf(2, "minishell: %s\n", cntx.error_message);
			gc_free(cntx.error_message);
		}
		return (NULL);
	}
	return (command_list);
}
