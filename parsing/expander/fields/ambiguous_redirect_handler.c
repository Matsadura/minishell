/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambiguous_redirect_handler.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberkass <aberkass@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 16:32:35 by aberkass          #+#    #+#             */
/*   Updated: 2025/06/13 16:32:49 by aberkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/**
 * is_redirect_operator - check if token type is a redirection operator
 * @type: token type to check
 * return: 1 if token type is redirection operator or 0 otherwise
 */
static int	is_redirect_operator(t_token_type type)
{
	return (type == REDIRECT_IN || type == REDIRECT_OUT
		|| type == HEREDOC || type == APPEND);
}

/**
 * set_redirect_context - update context of redirection tracking
 * @token: current processed token
 * @prev_token: previous token
 * @cntxt: field context to update
 */
void	set_redirect_context(t_token *token, t_token *prev_token,
		t_field_context *cntxt)
{
	if (prev_token != NULL)
		cntxt->prev_token_type = prev_token->type;
	else
		cntxt->prev_token_type = 0;
	cntxt->is_redirect_target = (prev_token != NULL
			&& is_redirect_operator(prev_token->type)
			&& token->type == WORD);
}

/**
 * is_valid_redirect_target - check if fields represent a valid redirect target
 * @fields: array of fields after splitting
 * return: 1 if the valid or 0 if invald
 */
static int	is_valid_redirect_target(char **fields)
{
	if (fields == NULL || fields[0] == NULL)
		return (0);
	if (fields[1] != NULL)
		return (0);
	if (fields[0][0] == '\0')
		return (0);
	return (1);
}

/**
 * is_ambiguous_redirect - check for ambiguous redirection after splitting
 * @fields: array of fields after splitting
 * @cntxt: field context contain redirect info
 * return: 1 if ambiguous redirect or 0 if not
 */
int	is_ambiguous_redirect(char **fields, t_field_context *cntxt)
{
	if (cntxt->is_redirect_target == 0)
		return (0);
	if (is_valid_redirect_target(fields) == 0)
	{
		ft_dprintf(2, "minishell: ambiguous redirect\n");
		return (1);
	}
	return (0);
}
