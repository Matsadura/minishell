/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberkass <aberkass@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 15:00:16 by aberkass          #+#    #+#             */
/*   Updated: 2025/05/28 18:07:19 by aberkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	if (cntx->quote_removal == 0)
		cntx->state = NORMAL;
	len = ft_strlen(token);
	i = 0;
	while (i < len)
		i = process_char(token, &res, i, cntx);
	return (res);
}

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
