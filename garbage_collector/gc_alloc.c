/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_alloc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberkass <aberkass@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 20:29:07 by aberkass          #+#    #+#             */
/*   Updated: 2025/05/22 20:29:12 by aberkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc_header.h"

/**
 * gc_alloc - allocates memory and tracks it in the garbage collector
 * @size: Size in bytes to allocate
 * return: pointer to allocated memory or NULL on failure
 */
void	*gc_alloc(size_t size)
{
	void	*address;
	t_gc	*gc;

	address = malloc(size);
	if (address == NULL)
		return (NULL);
	gc = get_gc_head();
	if (gc_add_node(gc, address) != 0)
	{
		free(address);
		return (NULL);
	}
	return (address);
}

/**
 * gc_strldup - duplicates a string with length limit using garbage collection
 * @str: string to duplicate
 * @len: length to copy
 * return: pointer to duplicated string or NULL on failure
 */
char	*gc_strldup(const char *str, size_t len)
{
	char	*dup;

	dup = gc_alloc(len + 1);
	if (dup == NULL)
		return (NULL);
	ft_strlcpy(dup, str, len + 1);
	return (dup);
}

/**
 * gc_free - frees memory and removes it from garbage collector tracking
 * @address: pointer to memory to free
 */
void	gc_free(void *address)
{
	t_gc	*gc;

	if (address == NULL)
		return ;
	gc = get_gc_head();
	gc_delete_node(gc, address);
	return ;
}

/**
 * gc_cleanup - frees all memory tracked by the garbage collector
 */
void	gc_cleanup(void)
{
	t_gc	*gc;

	gc = get_gc_head();
	free_all(gc);
	return ;
}
