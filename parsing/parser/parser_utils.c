/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberkass <aberkass@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 21:25:52 by aberkass          #+#    #+#             */
/*   Updated: 2025/05/06 03:15:30 by aberkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * is_redirection - checks if a token type represents a redirection operator
 * @type: the token type to check
 * return: 1 if token is a redirection operator 0 if it's not
 */
int	is_redirection(t_token_type type)
{
	return (type == REDIRECT_IN || type == REDIRECT_OUT
		|| type == APPEND || type == HEREDOC);
}

/**
 * set_syntax_error - sets a syntax error in the parser context
 * @cntx: parser context to update with error information
 * @message: error message string to store
 */
void	set_syntax_error(t_pars_context *cntx, char *message)
{
	cntx->has_syntax_error = 1;
	cntx->error_message = gc_strldup(message, ft_strlen(message));
}

/**
 * consume_token - advances the current token pointer to the next token
 * @cntx: parser context containing the current token pointer
 */
void	consume_token(t_pars_context *cntx)
{
	if (cntx->current_token != NULL)
		cntx->current_token = cntx->current_token->next;
}
