/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   field_checker.c                                    :+:      :+:    :+:   */
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
 * should_split_export_arg - checks if an export token needs to be split or no
 * @token: the export arg to evaluate for splitting
 * @cntxt: field context to update with splitting decision
 * return: 1 if token should be split 0 if it shouldn't
 */
int	should_split_export_arg(t_token *token, t_field_context *cntxt)
{
	char	*equal_pos;
	char	*ptr;

	equal_pos = ft_strchr(token->value, '=');
	if (equal_pos != NULL)
	{
		ptr = token->value;
		while (ptr < equal_pos)
		{
			if (is_white_space(*ptr) == 1)
			{
				cntxt->needs_splitting = 1;
				return (1);
			}
			ptr++;
		}
	}
	cntxt->needs_splitting = 0;
	return (0);
}

/**
 * handle_word_splitting - handle word token splitting logic
 * @token: the token to evaluate
 * @cntxt: field context
 * @env: environment list
 * return: 1 if token should be split, 0 otherwise
 */
static int	handle_word_splitting(t_token *token, t_field_context *cntxt,
	char **env)
{
	char	*ifs;

	if (token->was_quoted == 1)
	{
		cntxt->needs_splitting = 0;
		return (0);
	}
	if (cntxt->is_redirect_target == 1)
	{
		cntxt->needs_splitting = 1;
		return (1);
	}
	ifs = get_ifs_value(env);
	if (contains_ifs_character(token->value, ifs))
	{
		cntxt->needs_splitting = 1;
		return (1);
	}
	return (0);
}

/**
 * should_split_token_ifs - checks if a token needs to be split into fields 
 * @token: the token to evaluate for splitting
 * @cntxt: field context to update with splitting decision
 * @env: environment list to get IFS from
 * return: 1 if token should be split 0 if it shouldn't
 */
int	should_split_token_ifs(t_token *token, t_token *prev_token,
		t_field_context *cntxt, char **env)
{
	set_redirect_context(token, prev_token, cntxt);
	if (prev_token != NULL && ft_strcmp(prev_token->value, "export") == 0)
		return (should_split_export_arg(token, cntxt));
	if (token->type == WORD && token->needs_splitting)
		return (handle_word_splitting(token, cntxt, env));
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
