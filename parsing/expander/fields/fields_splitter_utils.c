/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fields_splitter_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberkass <aberkass@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 14:00:16 by aberkass          #+#    #+#             */
/*   Updated: 2025/06/01 22:39:05 by aberkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/**
 * contains_whitespace - checks if a string contains any whitespace characters
 * @str: the string to check for whitespace
 * return: 1 if whitespace is found 0 if not
 */
int	contains_whitespace(char *str)
{
	int	i;

	if (str == NULL)
		return (0);
	i = 0;
	while (str[i] != '\0')
	{
		if (is_white_space(str[i]))
			return (1);
		i++;
	}
	return (0);
}

/**
 * should_split_token - checks if a token needs to be split into fields 
 * @token: the token to evaluate for splitting
 * @cntxt: field context to update with splitting decision
 * return: 1 if token should be split 0 if it shouldn't
 */
int	should_split_token(t_token *token, t_field_context *cntxt)
{
	if (token->type == WORD && token->needs_spliting
		&& contains_whitespace(token->value))
	{
		cntxt->needs_splitting = 1;
		return (1);
	}
	cntxt->needs_splitting = 0;
	return (0);
}

/**
 * free_fields_array - frees an array of field strings
 * @fields: array of strings to be freed
 */
void	free_fields_array(char **fields)
{
	int	i;

	if (fields == NULL)
		return ;
	i = 0;
	while (fields[i] != NULL)
	{
		gc_free(fields[i]);
		i++;
	}
	gc_free(fields);
}
