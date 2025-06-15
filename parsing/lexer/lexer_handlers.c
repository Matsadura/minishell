/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberkass <aberkass@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 20:36:03 by aberkass          #+#    #+#             */
/*   Updated: 2025/05/22 20:36:06 by aberkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * skip_to_matching_quote - finds the matching closing quote
 * @lexer: pointer to the lexer structure  
 * @quote_char: the quote character to match
 * returns: 1 if matching quote found or 0 if not found (unclosed quote)
 */
static int	skip_to_matching_quote(t_lexer *lexer, char quote_char)
{
	lexer->current++;
	while (lexer->current < lexer->input_len
		&& lexer->input[lexer->current] != quote_char)
		lexer->current++;
	if (lexer->current < lexer->input_len)
	{
		lexer->current++;
		return (1);
	}
	ft_dprintf(2, "syntax error: unclosed quotes\n");
	return (0);
}

/**
 * operators - processes operators including double operators (>>, <<)
 * @lexer: pointer to the lexer structure
 */
void	operators(t_lexer *lexer)
{
	char	op;

	op = lexer->input[lexer->current];
	lexer->current++;
	if (lexer->current < lexer->input_len
		&& lexer->input[lexer->current] == op
		&& (op == '>' || op == '<'))
		lexer->current++;
}

/**
 * is_token_boundary - checks if current position is a token boundary
 * @lexer: pointer to the lexer structure
 * returns: 1 if at token boundary, 0 otherwise
 */
static int	is_token_boundary(t_lexer *lexer)
{
	char	c;

	if (lexer->current >= lexer->input_len)
		return (1);
	c = lexer->input[lexer->current];
	return (is_white_space(c) || is_operator(c));
}

/**
 * words - processes word tokens including complex quote combinations
 * @lexer: pointer to the lexer structure
 * returns: 1 on success and 0 on syntax error unclosed quotes
 */
int	words(t_lexer *lexer)
{
	char	quote_char;

	while (lexer->current < lexer->input_len && !is_token_boundary(lexer))
	{
		if (is_quote(lexer->input[lexer->current]))
		{
			quote_char = lexer->input[lexer->current];
			if (skip_to_matching_quote(lexer, quote_char) == 0)
				return (0);
		}
		else
			lexer->current++;
	}
	return (1);
}
