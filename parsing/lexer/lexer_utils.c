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

void	skip_whitespaces(t_lexer *lexer)
{
	while (lexer->current < lexer->input_len
		&& is_white_space(lexer->input[lexer->current]))
		lexer->current++;
}

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

void	operators(t_lexer *lexer)
{
	lexer->current++;
	if (lexer->current < lexer->input_len
		&& (lexer->input[lexer->current] == '>'
			|| lexer->input[lexer->current] == '<')
		&& lexer->input[lexer->current] == lexer->input[lexer->current - 1])
		lexer->current++;
}

void	words(t_lexer *lexer)
{
	while (lexer->current < lexer->input_len
		&&!is_white_space(lexer->input[lexer->current])
		&& !is_operator(lexer->input[lexer->current]))
		lexer->current++;
}

void	print_lexemes(const char *str)
{
	printf("lexeme: %s\n", str);
}
