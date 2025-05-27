/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberkass <aberkass@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 20:35:11 by aberkass          #+#    #+#             */
/*   Updated: 2025/05/22 20:35:13 by aberkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"
# include "tokeniser.h"

typedef struct s_lexer
{
	const char	*input;
	size_t		input_len;
	size_t		start_indx;
	size_t		current;
}	t_lexer;

//lexing
t_token	*lex_input(const char *input);

//character check
int		is_quote(char c);
int		is_operator(char c);
int		is_white_space(char c);

//utils
void	skip_whitespaces(t_lexer *lexer);
void	quotes(t_lexer *lexer);
void	operators(t_lexer *lexer);
void	words(t_lexer *lexer);

#endif
