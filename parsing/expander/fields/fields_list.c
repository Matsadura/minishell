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

/**
 * clean_list - frees all nodes and their values in a token list
 * @list: linked list of tokens to be freed
 */
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

/**
 * create_field_list - converts an array of field strings into a token list
 * @fields: array of field strings
 * return: head of the created token list or NULL on failure
 */
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

/**
 * split_token - splits a token into multiple tokens based on whitespace
 * @token: the token to potentially split
 * @cntxt: field context containing splitting flags and state
 * return: single token or list of tokens after splitting
 */
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

/**
 * append_token_list - appends one token list to the end of another
 * @dest: pointer to the destination list head
 * @src: source list to append
 */
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
