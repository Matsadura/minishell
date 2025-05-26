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

void	process_lexeme(t_lexer *lexer)
{
	char	c;

	lexer->start_indx = lexer->current;
	c = lexer->input[lexer->current];
	if (is_quote(c))
		quotes(lexer);
	else if (is_operator(c))
		operators(lexer);
	else
		words(lexer);
}

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
		if (lexer->current >= lexer->input_len)
			break ;
		process_lexeme(lexer);
		lexeme = gc_strldup(lexer->input + lexer->start_indx,
				lexer->current - lexer->start_indx);
		if (lexeme == NULL)
			return (NULL);
		token_list = tokeniser(lexeme, token_list);
	}
	return (token_list);
}
