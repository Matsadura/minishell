/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberkass <aberkass@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 08:20:10 by aberkass          #+#    #+#             */
/*   Updated: 2025/06/19 08:20:19 by aberkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * init_expansion_context - initialises the expansion context structure
 * @cntxt: pointer to the expansion context to initialize
 * @env: environment array 
 * @exit_status: the last command exit status for $? expansion
 */
void	init_expansion_context(t_exp_context *cntxt, char **env,
									int exit_status)
{
	cntxt->env = env;
	cntxt->last_exit_status = exit_status;
	cntxt->state = NORMAL;
	cntxt->quote_removal = 0;
	cntxt->needs_splitting = 0;
}

/**
 * set_heredoc_targets - mark heredoc targets
 * @tokens: token list to process
 */
void	mark_tokens(t_token *tokens)
{
	t_token	*current;
	int		index;

	current = tokens;
	index = 0;
	while (current->next != NULL)
	{
		if (current->type == HEREDOC)
			current->next->is_heredoc_target = 1;
		current->index = index;
		index++;
		current = current->next;
	}
}

/**
 * process_token_expansion - processes a single token for expansion
 * @token: the token to be processed and expanded
 * @context: expansion context containing state and environment info
 * return: expanded token value string, or NULL if no expansion needed
 */
char	*process_token_expansion(t_token *token, t_exp_context *cntxt)
{
	char	*expanded;

	if ((token->type == D_QUOTE || token->type == S_QUOTE)
		&& token->is_heredoc_target == 0)
	{
		cntxt->needs_splitting = 0;
		expanded = process_quoted_token(token, cntxt);
	}
	else if (token->type == WORD && token->is_heredoc_target == 0)
	{
		expanded = expand_token(token->value, cntxt);
		if (ft_strcmp(expanded, token->value))
			cntxt->needs_splitting = 1;
	}
	else
	{
		expanded = NULL;
		cntxt->needs_splitting = 0;
	}
	return (expanded);
}
