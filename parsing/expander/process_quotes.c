/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberkass <aberkass@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 16:15:16 by aberkass          #+#    #+#             */
/*   Updated: 2025/05/28 18:07:19 by aberkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * process_quoted_token - processes tokens that are enclosed in quotes
 * @val: the token value including the quotes
 * @type: the type of token
 * @cntx: expansion context containing state and environment information
 * return: processed string with quotes removed and expansions applied
 */
char	*process_quoted_token(char *val, t_token_type type, t_exp_context *cntx)
{
	char	*res;
	char	*tmp;

	res = NULL;
	cntx->quote_removal = 1;
	if (type == S_QUOTE)
	{
		cntx->state = SINGLE_QUOTES;
		res = remove_outer_quotes(val, '\'');
	}
	else
	{
		cntx->state = DOUBLE_QUOTES;
		tmp = remove_outer_quotes(val, '"');
		res = expand_token(tmp, cntx);
	}
	return (res);
}

/**
 * remove_outer_quotes - removes the outer matching quotes from a string
 * @token_str: the string potentially enclosed in quotes
 * @quote_char: the quote character to remove (' or ")
 * return: new string with outer quotes removed, or original string if no quotes
 */
char	*remove_outer_quotes(char *token_str, char quote_char)
{
	char	*res;
	int		len;

	if (token_str == NULL || token_str[0] != quote_char)
		return (gc_strldup(token_str, ft_strlen(token_str)));
	len = ft_strlen(token_str);
	if (len < 2 || token_str[len - 1] != quote_char)
	{
		ft_dprintf(2, "syntax error: unclosed quote!\n");
		return (gc_strldup(token_str, len));
	}
	res = gc_strldup(token_str + 1, len - 2);
	return (res);
}
