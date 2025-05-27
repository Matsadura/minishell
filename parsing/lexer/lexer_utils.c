/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberkass <aberkass@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 20:36:03 by aberkass          #+#    #+#             */
/*   Updated: 2025/05/22 20:36:06 by aberkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * skip_whitespaces - advances lexer position past all whitespace characters
 * @lexer: pointer to the lexer structure
 */
void	skip_whitespaces(t_lexer *lexer)
{
	while (lexer->current < lexer->input_len
		&& is_white_space(lexer->input[lexer->current]))
		lexer->current++;
}

/**
 * quotes - processes quoted strings by finding the matching closing quote
 * @lexer: pointer to the lexer structure
 */
void	quotes(t_lexer *lexer)
{
	char	quote;

	quote = lexer->input[lexer->current++];
	while (lexer->current < lexer->input_len
		&& lexer->input[lexer->current] != quote)
		lexer->current++;
	if (lexer->current < lexer->input_len)
		lexer->current++;
}

/**
 * operators - processes operators including double operators (>>, <<)
 * @lexer: pointer to the lexer structure
 */
void	operators(t_lexer *lexer)
{
	lexer->current++;
	if (lexer->current < lexer->input_len
		&& (lexer->input[lexer->current] == '>'
			|| lexer->input[lexer->current] == '<')
		&& lexer->input[lexer->current] == lexer->input[lexer->current - 1])
		lexer->current++;
}

/**
 * words - processes word tokens until whitespace or operator is encountered
 * @lexer: pointer to the lexer structure
 */
void	words(t_lexer *lexer)
{
	while (lexer->current < lexer->input_len
		&&!is_white_space(lexer->input[lexer->current])
		&& !is_operator(lexer->input[lexer->current]))
		lexer->current++;
}
