/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fields_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberkass <aberkass@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 14:00:16 by aberkass          #+#    #+#             */
/*   Updated: 2025/06/01 22:39:05 by aberkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	clean_list(t_token *list)
{
	t_token	*temp;

	while (list != NULL)
	{
		temp = list;
		list = list->next;
		gc_free(temp->value);
		gc_free(temp);
	}
}

static t_token	*create_field_list(char **fields)
{
	int		i;
	t_token	*list;
	t_token	*node;

	if (fields == NULL)
		return (NULL);
	list = NULL;
	i = 0;
	while (fields[i] != NULL)
	{
		node = create_token_node(fields[i], WORD);
		if (node == NULL)
		{
			clean_list(list);
			return (NULL);
		}
		add_token(&list, node);
		i++;
	}
	return (list);
}

t_token	*split_token(t_token *token, t_field_context *cntxt)
{
	char	**fields;
	t_token	*field_list;

	if (cntxt->needs_splitting == 0)
		return (create_token_node(token->value, token->type));
	fields = ft_split_by_space(token->value);
	if (fields == NULL || fields[0] == NULL)
	{
		free_fields_array(fields);
		return (create_token_node(token->value, token->type));
	}
	field_list = create_field_list(fields);
	free_fields_array(fields);
	return (field_list);
}

void	append_token_list(t_token **dest, t_token *src)
{
	t_token	*current;

	if (src == NULL)
		return ;
	if (*dest == NULL)
	{
		*dest = src;
		return ;
	}
	current = *dest;
	while (current->next != NULL)
		current = current->next;
	current->next = src;
}
