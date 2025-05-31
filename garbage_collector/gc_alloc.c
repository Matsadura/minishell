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
 * gc_strljoin - joins two strings with length limit using garbage collection
 * @s1: first string
 * @s2: second string
 * @len: length limit for the joined string
 * return: pointer to the joined string or NULL on failure
 */
char	*gc_strljoin(const char *s1, const char *s2, size_t len)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*joined;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	s1_len = 0;
	s2_len = 0;
	if (s1 != NULL)
		s1_len = ft_strlen(s1);
	if (s2 != NULL)
		s2_len = ft_strlen(s2);
	if (s1_len + s2_len > len)
		return (NULL);
	joined = gc_alloc(s1_len + s2_len + 1);
	if (joined == NULL)
		return (NULL);
	ft_strlcpy(joined, s1, s1_len + 1);
	ft_strlcat(joined, s2, s1_len + s2_len + 1);
	return (joined);
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
