/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberkass <aberkass@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 20:35:18 by aberkass          #+#    #+#             */
/*   Updated: 2025/05/22 20:35:21 by aberkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENISER_H
# define TOKENISER_H

# include "minishell.h"
# include "lexer.h"

typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIRECT_IN,
	REDIRECT_OUT,
	HERDOC,
	APPEND,
	S_QUOTE,
	D_QUOTE
}	t_token_type;

typedef struct s_token
{
	char				*value;
	t_token_type		type;
	struct s_token		*next;
}	t_token;

//to get token type
t_token_type	get_token_type(const char *value, size_t len);

//to create tokens lis
t_token			*create_token_node(const char *value, t_token_type type);
void			add_token(t_token **head, t_token *new_token);

//tokeniser
t_token			*tokeniser(const char *lexeme, t_token *token_list);

#endif
