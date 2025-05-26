/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberkass <aberkass@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 20:29:40 by aberkass          #+#    #+#             */
/*   Updated: 2025/05/22 20:29:43 by aberkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc_header.h"

/**
 * gc_init - initialises the garbage collector structure
 * @gc: pointer to garbage collector structure to initialise
 */
void	gc_init(t_gc *gc)
{
	gc->head = NULL;
	return ;
}

/**
 * get_gc_head - gets the singleton garbage collector instance
 * return: pointer to the global garbage collector structure
 */
t_gc	*get_gc_head(void)
{
	static t_gc	gc = {NULL};

	return (&gc);
}

/**
 * gc_add_node - adds a memory address to the garbage collector list
 * @gc: pointer to garbage collector structure
 * @address: memory address to track
 * return: 0 on success -1 on failure
 */
int	gc_add_node(t_gc *gc, void *address)
{
	t_gc_node	*new_node;

	new_node = malloc(sizeof(t_gc_node));
	if (new_node == NULL)
		return (-1);
	new_node->address = address;
	new_node->next = gc->head;
	gc->head = new_node;
	return (0);
}

/**
 * gc_delete_node - removes and frees a specific memory address from the list
 * @gc: pointer to garbage collector structure
 * @address: memory address to remove from tracking
 */
void	gc_delete_node(t_gc *gc, void *address)
{
	t_gc_node	*current;
	t_gc_node	*to_delete;

	if (gc == NULL || gc->head == NULL || address == NULL)
		return ;
	current = gc->head;
	if (current->address == address)
	{
		gc->head = current->next;
		free(current->address);
		free(current);
		return ;
	}
	while (current != NULL && current->next != NULL)
	{
		if (current->next->address == address)
		{
			to_delete = current->next;
			current->next = current->next->next;
			free(to_delete->address);
			free(to_delete);
			return ;
		}
		current = current->next;
	}
}

/**
 * free_all - frees all memory tracked by the garbage collector
 * @gc: pointer to garbage collector structure
 */
void	free_all(t_gc *gc)
{
	t_gc_node	*current;
	t_gc_node	*next;

	current = gc->head;
	while (current != NULL)
	{
		next = current->next;
		free(current->address);
		free(current);
		current = next;
	}
	gc->head = NULL;
	return ;
}
