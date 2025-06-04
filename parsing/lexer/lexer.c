/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberkass <aberkass@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 20:35:54 by aberkass          #+#    #+#             */
/*   Updated: 2025/05/22 20:35:56 by aberkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * init_lexer - initialises a new lexer structure for given input
 * @input: the input string to be lexed
 * return: pointer to initialized lexer or NULL on failure
 */
t_lexer	*init_lexer(const char *input)
{
	t_lexer	*lexer;

	lexer = gc_alloc(sizeof(t_lexer));
	if (lexer == NULL)
		return (NULL);
	lexer->input = input;
	lexer->input_len = ft_strlen(input);
	lexer->start_indx = 0;
	lexer->current = 0;
	return (lexer);
}

/**
 * process_lexeme - processes a single lexeme based on its first character
 * @lexer: pointer to the lexer structure
 * return: 1 on success and 0 on faillure
 */
static int	process_lexeme(t_lexer *lexer)
{
	char	c;

	lexer->start_indx = lexer->current;
	c = lexer->input[lexer->current];
	if (is_operator(c))
	{
		operators(lexer);
		return (1);
	}
	return (words(lexer));
}

/**
 * lex_input - main lexing function that tokenises the entire input string
 * @input: the input string to be lexed and tokenised
 * return: pointer to the token list or NULL on failure
 */
t_token	*lex_input(const char *input)
{
	t_lexer		*lexer;
	t_token		*token_list;
	const char	*lexeme;

	lexer = init_lexer(input);
	token_list = NULL;
	while (lexer->current < lexer->input_len)
	{
		skip_whitespaces(lexer);
		if (process_lexeme(lexer) == 0)
			return (NULL);
		lexeme = gc_strldup(lexer->input + lexer->start_indx,
				lexer->current - lexer->start_indx);
		if (lexeme == NULL)
			return (NULL);
		token_list = tokeniser(lexeme, token_list);
	}
	return (token_list);
}
