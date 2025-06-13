/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberkass <aberkass@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 20:36:30 by aberkass          #+#    #+#             */
/*   Updated: 2025/05/22 20:38:23 by aberkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * is_simple_quoted - checks if token is a simple quoted string
 * @value: the lexeme string
 * @len: the length of the lexeme
 * @quote_char: the quote character to check for
 * returns: 1 if it's a simple quoted token or 0 if it's not
 */
static int	is_simple_quoted(const char *value, size_t len, char quote_char)
{
	return (len >= 2 && value[0] == quote_char && value[len - 1] == quote_char);
}

/**
 * get_token_type - determines the token type based on lexeme value and length
 * @value: the lexeme string
 * @len: the length of the lexeme
 * return: the appropriate token type
 */
t_token_type	get_token_type(const char *value, size_t len)
{
	if (len == 1)
	{
		if (value[0] == '|')
			return (PIPE);
		else if (value[0] == '>')
			return (REDIRECT_OUT);
		else if (value[0] == '<')
			return (REDIRECT_IN);
	}
	if (len == 2)
	{
		if (value[0] == '>' && value[1] == '>')
			return (APPEND);
		else if (value[0] == '<' && value[1] == '<')
			return (HEREDOC);
	}
	if (is_simple_quoted(value, len, '"'))
		return (D_QUOTE);
	else if (is_simple_quoted(value, len, '\''))
		return (S_QUOTE);
	return (WORD);
}

/**
 * is_quoted_token - checks if a token type represents a quoted stirng
 * @type: the token type to check
 * @value: the token value to check for quote characters
 * return: 1 if token is quoted or 0 if it's not
 */
static int	is_quoted_token(t_token_type type, const char *value)
{
	int	i;

	if (type == D_QUOTE || type == S_QUOTE)
		return (1);
	i = 0;
	while (value[i] != '\0')
	{
		if (value[i] == '"' || value[i] == '\'')
			return (1);
		i++;
	}
	return (0);
}

/**
 * create_token_node - creates a new token node with given value and type
 * @value: the token value string
 * @type: the token type
 * return: pointer to new token node or NULL on failure
 */
t_token	*create_token_node(const char *value, t_token_type type)
{
	t_token	*new_token;

	new_token = gc_alloc(sizeof(t_token));
	if (new_token == NULL)
		return (NULL);
	new_token->value = gc_strldup(value, ft_strlen(value));
	new_token->type = type;
	new_token->was_quoted = is_quoted_token(type, value);
	new_token->needs_splitting = 0;
	new_token->next = NULL;
	return (new_token);
}

/**
 * add_token - adds a new token to the end of the token list
 * @head: pointer to the head of the token list
 * @new_token: the new token to add
 */
void	add_token(t_token **head, t_token *new_token)
{
	t_token	*tmp;

	if (*head == NULL)
	{
		*head = new_token;
		return ;
	}
	tmp = *head;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new_token;
	return ;
}
