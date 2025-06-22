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
 * expander - main expansion function that processes a token list
 * @tokens: linked list of tokens to be expanded
 * @env: environment array
 * @exit_status: last command exit status for $? variable
 * return: pointer to the modified token list (same as input)
 */
t_token	*expander(t_token *tokens, char **env, int exit_status)
{
	char			*expanded;
	t_exp_context	cntxt;
	t_token			*current;

	init_expansion_context(&cntxt, env, exit_status);
	mark_tokens(tokens);
	current = tokens;
	while (current != NULL)
	{
		expanded = process_token_expansion(current, &cntxt);
		if (expanded != NULL)
		{
			current->value = expanded;
			current->needs_splitting = cntxt.needs_splitting;
		}
		if (current->type == S_QUOTE || current->type == D_QUOTE)
			current->type = WORD;
		current = current->next;
	}
	tokens = field_splitter(tokens, env);
	return (tokens);
}
