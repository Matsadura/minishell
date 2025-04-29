/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaoui <zzaoui@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 11:51:58 by zzaoui            #+#    #+#             */
/*   Updated: 2024/11/03 23:01:16 by zzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * ft_strnstr - locate a substring in a string
 * @haystack: the string to search in
 * @needle: the string to search for
 * @len: the max length to search in
 * Return: Haystack if needle is empty, NULL if needle isn't in haystack
 *		otherwise a pointer to the first character of the first occurrence
 *		of needle is returned
 */
char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	counter;
	size_t	first;

	if ((ft_strlen(haystack) == 0 && ft_strlen(needle) == 0)
		|| ft_strlen(needle) == 0)
		return ((char *) haystack);
	i = 0;
	while (i <= len - ft_strlen(needle) && haystack[i])
	{
		counter = 0;
		if (haystack[i + counter] == needle[counter])
		{
			first = i;
			while (i + counter < len
				&& needle[counter]
				&& haystack[i + counter] == needle[counter])
				counter++;
			if (counter == ft_strlen(needle))
				return ((char *)(haystack + first));
		}
		i++;
	}
	return (NULL);
}
