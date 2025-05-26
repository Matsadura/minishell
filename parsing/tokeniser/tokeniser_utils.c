/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberkass <aberkass@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 20:36:30 by aberkass          #+#    #+#             */
/*   Updated: 2025/05/22 20:38:23 by aberkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
			return (HERDOC);
	}
	if (len > 0 && value[0] == '"')
		return (D_QUOTE);
	else if (len > 0 && value[0] == '\'')
		return (S_QUOTE);
	return (WORD);
}

t_token	*create_token_node(const char *value, t_token_type type)
{
	t_token	*new_token;

	new_token = gc_alloc(sizeof(t_token));
	if (new_token == NULL)
		return (NULL);
	new_token->value = gc_strldup(value, ft_strlen(value));
	new_token->type = type;
	new_token->next = NULL;
	return (new_token);
}

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
