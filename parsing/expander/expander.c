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

static void	init_expansion_context(t_exp_context *context, char **env, int exit_status)
{
	context->env = env;
	context->last_exit_status = exit_status;
	context->state = NORMAL;
	context->quote_removal = 0;
}

t_token	*expander(t_token *tokens, char **env, int exit_status)
{
	char			*expanded;
	t_exp_context	context;
	t_token			*current;

	init_expansion_context(&context, env, exit_status);
	current = tokens;
	while (current != NULL)
	{
		if (current->type == D_QUOTE || current->type == S_QUOTE)
			expanded = process_quoted_token(current->value,
					current->type, &context);
		else if (current->type == WORD)
			expanded = expand_token(current->value, &context);
		else
			expanded = NULL;
		if (expanded != NULL)
			current->value = expanded;
		current = current->next;
	}
	return (tokens);
}
