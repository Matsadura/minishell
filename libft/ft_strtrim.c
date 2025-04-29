/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaoui <zzaoui@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 09:31:20 by zzaoui            #+#    #+#             */
/*   Updated: 2024/11/04 15:36:00 by zzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * in_set - Checks the existance of a char in a set
 * @c1: the char to find
 * @set: the set to look in
 * Return: 1 if found, 0 otherwise.
 */
static int	in_set(char const c1, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c1 == set[i])
			return (1);
		i++;
	}
	return (0);
}

/**
 * front - Calculates the count of set chars from the front of str
 * @s1: the string
 * @set: the set
 * Return: the count
 */
static int	front(char const *s1, char const *set)
{
	size_t	i;

	i = 0;
	while (in_set(s1[i], set))
		i++;
	return (i);
}

/**
 * back - Calculates the count of set chars from the back of str
 * @s1: the string
 * @set: the set
 * Return: the count
 */
static int	back(char const *s1, char const *set)
{
	size_t	j;

	j = ft_strlen(s1);
	while (j > 0 && in_set(s1[j - 1], set))
		j--;
	return (j);
}

/**
 * ft_strtrim - Allocates a copy of 's1' with the characters specified
 *		in 'set' removed from beginning and the end of the string.
 * @s1: the string to be trimmed
 * @set: the reference set of characters to trim
 * Return: the trimmed string, otherwise NULL.
 */
char	*ft_strtrim(char const *s1, char const *set)
	{
	size_t	i;
	size_t	j;
	size_t	k;
	char	*copy;

	if (s1 == NULL || set == NULL)
		return (NULL);
	i = front(s1, set);
	j = back(s1, set);
	if (j < i)
		return (ft_strdup(""));
	copy = (char *) malloc(j - i + 1);
	if (copy == NULL)
		return (NULL);
	k = 0;
	while (i < j)
	{
		copy[k] = s1[i];
		k++;
		i++;
	}
	copy[k] = '\0';
	return (copy);
}
