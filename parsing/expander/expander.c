/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberkass <aberkass@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 16:58:11 by aberkass          #+#    #+#             */
/*   Updated: 2025/05/27 16:58:13 by aberkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * init_expansion_context - initialises the expansion context structure
 * @cntxt: pointer to the expansion context to initialize
 * @env: environment array 
 * @exit_status: the last command exit status for $? expansion
 */
static void	init_expansion_context(t_exp_context *cntxt, char **env,
									int exit_status)
{
	cntxt->env = env;
	cntxt->last_exit_status = exit_status;
	cntxt->state = NORMAL;
	cntxt->quote_removal = 0;
	cntxt->needs_spliting = 0;
}

/**
 * process_token_expansion - processes a single token for expansion
 * @token: the token to be processed and expanded
 * @context: expansion context containing state and environment info
 * return: expanded token value string, or NULL if no expansion needed
 */
static char	*process_token_expansion(t_token *token, t_exp_context *context)
{
	char	*expanded;

	context->needs_spliting = 1;
	if (token->type == D_QUOTE || token->type == S_QUOTE)
	{
		context->needs_spliting = 0;
		expanded = process_quoted_token(token->value,
				token->type, context);
	}
	else if (token->type == WORD)
		expanded = expand_token(token->value, context);
	else
	{
		expanded = NULL;
		context->needs_spliting = 0;
	}
	return (expanded);
}

/**
 * expander - main expansion function that processes a token list
 * @tokens: linked list of tokens to be expanded
 * @env: environment array
 * @exit_status: last command exit status for $? variable
 * return: pointer to the modified token list (same as input)
 */
t_token	*expander(t_token *tokens, char **env, int exit_status)
{
	char			*expanded;
	t_exp_context	context;
	t_token			*current;

	init_expansion_context(&context, env, exit_status);
	current = tokens;
	while (current != NULL)
	{
		expanded = process_token_expansion(current, &context);
		if (expanded != NULL)
		{
			current->value = expanded;
			current->needs_spliting = context.needs_spliting;
		}
		current = current->next;
	}
	return (tokens);
}
