/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberkass <aberkass@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 20:36:21 by aberkass          #+#    #+#             */
/*   Updated: 2025/05/22 20:36:23 by aberkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * tokeniser - creates a token from lexeme and adds it to the token list
 * @lexeme: the lexeme string to tokenize
 * @token_list: the existing token list to add to
 * return: updated token list with new token added
 */
t_token	*tokeniser(const char *lexeme, t_token *token_list)
{
	t_token			*new_token;
	t_token_type	type;

	type = get_token_type(lexeme, ft_strlen(lexeme));
	new_token = create_token_node(lexeme, type);
	if (new_token == NULL)
		return (token_list);
	add_token(&token_list, new_token);
	return (token_list);
}
