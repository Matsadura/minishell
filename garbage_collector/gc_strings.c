/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_strings.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberkass <aberkass@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 12:00:16 by aberkass          #+#    #+#             */
/*   Updated: 2025/06/01 23:27:27 by aberkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc_header.h"

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
 * gc_substr - creates a substring from a given string using garbage collection
 * @s: source string
 * @start: starting index of the substring
 * @len: maximum length of the substring
 * return: pointer to the new substring or NULL on failure
 */
char	*gc_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	l;

	if (!s)
		return (NULL);
	l = ft_strlen(s);
	if (!s[0] || start > l)
		return (gc_strldup("", 1));
	if (len > l - start)
		len = l - start;
	sub = (char *)gc_alloc(len + 1);
	if (!sub)
		return (NULL);
	ft_strlcpy(sub, s + start, len + 1);
	return (sub);
}
