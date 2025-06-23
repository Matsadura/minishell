/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_processing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberkass <aberkass@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 16:15:16 by aberkass          #+#    #+#             */
/*   Updated: 2025/05/28 18:07:19 by aberkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * remove_outer_quotes - removes the outer matching quotes from a string
 * @token_str: the string potentially enclosed in quotes
 * @quote_char: the quote character to remove (' or ")
 * return: new string with outer quotes removed, or original string if no quotes
 */
static char	*remove_outer_quotes(char *token_str, char quote_char)
{
	char	*res;
	int		len;

	if (token_str == NULL)
		return (NULL);
	if (token_str[0] != quote_char)
		return (gc_strldup(token_str, ft_strlen(token_str)));
	len = ft_strlen(token_str);
	res = gc_strldup(token_str + 1, len - 2);
	return (res);
}

/**
 * remove_single_quotes - removes the single quotes from a string
 * @token_str: the string potentially enclosed in quotes
 * return: new string with single quotes removed
 */
static char	*remove_single_quotes(char *token_str)
{
	char	*res;
	int		j;
	int		i;

	res = gc_alloc(ft_strlen(token_str) + 1);
	if (res == NULL)
		return (NULL);
	j = 0;
	i = 0;
	while (token_str[i] != '\0')
	{
		if (token_str[i] != '\'')
		{
			res[j] = token_str[i];
			j++;
		}
		i++;
	}
	res[j] = '\0';
	return (res);
}

/**
 * process_quoted_token - processes tokens that are enclosed in quotes
 * @val: the token value including the quotes
 * @type: the type of token
 * @cntxt: expansion context containing state and environment information
 * return: processed string with quotes removed and expansions applied
 */
char	*process_quoted_token(char *val, t_token_type type, t_exp_context *cntx)
{
	char	*res;
	char	*tmp;

	res = NULL;
	cntx->quote_removal = 1;
	if (type == S_QUOTE)
		res = remove_single_quotes(val);
	else
	{
		tmp = remove_outer_quotes(val, '"');
		if (tmp == NULL)
			return (NULL);
		cntx->state = DOUBLE_QUOTES;
		res = expand_token(tmp, cntx);
	}
	return (res);
}

