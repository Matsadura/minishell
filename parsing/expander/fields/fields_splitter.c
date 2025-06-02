/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fields_splitter.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberkass <aberkass@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 12:15:16 by aberkass          #+#    #+#             */
/*   Updated: 2025/06/01 22:41:05 by aberkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/**
 * process_splittable_token - handles tokens that need field splitting
 * @token: the token to be split into multiple fields
 * @new_list: pointer to the new token list being built
 * @cntxt: field context containing splitting state information
 */
static void	process_splittable_token(t_token *token, t_token **new_list,
			t_field_context *cntxt)
{
	t_token	*split_tokens;

	split_tokens = split_token(token, cntxt);
	if (split_tokens != NULL)
		append_token_list(new_list, split_tokens);
}

/**
 * process_regular_token - handles tokens that don't need field splitting
 * @token: the token to copy without splitting
 * @new_list: pointer to the new token list being built
 */
static void	process_regular_token(t_token *token, t_token **new_list)
{
	t_token	*new_node;

	new_node = create_token_node(token->value, token->type);
	if (new_node != NULL)
		add_token(new_list, new_node);
}

/**
 * field_splitter - main field splitting function for token lists
 * @tokens: linked list of expanded tokens to process for field splitting
 * return: new token list with field splitting applied
 */
t_token	*field_splitter(t_token *tokens)
{
	t_token			*current;
	t_token			*new_list;
	t_field_context	cntxt;

	new_list = NULL;
	current = tokens;
	ft_memset(&cntxt, 0, sizeof(cntxt));
	while (current != NULL)
	{
		if (should_split_token(current, &cntxt))
			process_splittable_token(current, &new_list, &cntxt);
		else
			process_regular_token(current, &new_list);
		current = current->next;
	}
	return (new_list);
}
