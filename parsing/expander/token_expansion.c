/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberkass <aberkass@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 15:00:16 by aberkass          #+#    #+#             */
/*   Updated: 2025/05/28 18:07:19 by aberkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * expand_token - main token expansion function that processes the entire token
 * @token: the input token string to be expanded
 * @cntx: expansion context containing environment and state information
 * return: fully expanded token string or NULL on failure
 */
char	*expand_token(char *token, t_exp_context *cntx)
{
	char	*res;
	int		i;
	int		len;

	if (token == NULL)
		return (NULL);
	res = gc_alloc(1);
	if (res == NULL)
		return (NULL);
	res[0] = '\0';
	cntx->quote_removal = 0;
	cntx->state = NORMAL;
	len = ft_strlen(token);
	i = 0;
	while (i < len)
		i = process_char(token, &res, i, cntx);
	return (res);
}

/**
 * process_char - processes a single character during token expansion
 * @token: the input token string
 * @res: pointer to the result string
 * @i: current character index in the token
 * @cntx: expansion context for state management
 * return: next index position to process
 */
int	process_char(char *token, char **res, int i, t_exp_context *cntx)
{
	if (token[i] == '\'' && cntx->state != DOUBLE_QUOTES)
		return (handle_single_quotes(i, cntx));
	else if (token[i] == '"' && cntx->state != SINGLE_QUOTES)
		return (handle_double_quotes(i, cntx));
	else if (token[i] == '$' && cntx->state != SINGLE_QUOTES)
		return (handle_var_expansion(token, res, i, cntx));
	else
		return (handle_regular_character(token, res, i));
}
