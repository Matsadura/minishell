/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaoui <zzaoui@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 17:16:16 by zzaoui            #+#    #+#             */
/*   Updated: 2025/06/13 17:17:07 by zzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc_header.h"

/**
 * count_words - Counts the number of words in a string
 * @str: The string to count words in.
 * @c: The delimiter character.
 * Returns: The number of words in the string.
 */
static int	count_words(char const *str, char c)
{
	int	i;
	int	is_word;
	int	count;

	if (str == NULL || str[0] == '\0')
		return (0);
	i = 0;
	is_word = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c)
			is_word = 0;
		else if (is_word == 0)
		{
			is_word = 1;
			count++;
		}
		i++;
	}
	return (count);
}

/**
 * ft_dup - Duplicates a substring into a newly allocated string.
 * @word: The destination string.
 * @start: The start of the substring in the original string.
 * @len: The length of the substring to copy.
 * Returns: The duplicated string.
 */
static char	*ft_dup(char *word, char *start, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		word[i] = start[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

/**
 * get_next_word - Finds the next word in the string and updates the pointer.
 * @s: The string to search.
 * @c: The delimiter character.
 * @start: Pointer to store the start of the next word.
 * Returns: The length of the next word.
 */
static int	get_next_word(const char **s, char c, char **start)
{
	while (**s == c && **s)
		(*s)++;
	*start = (char *) *s;
	while (**s && **s != c)
		(*s)++;
	return (*s - *start);
}

/**
 * gc_split - Splits a string into an array of strings using a delimiter
 *            and allocates memory using the garbage collector.
 * @s: The string to split.
 * @c: The delimiter character.
 * Returns: An array of strings (NULL-terminated) or NULL on failure.
 */
char	**gc_split(char const *s, char c)
{
	int		index;
	char	**array;
	char	*start;

	if (s == NULL)
		return (NULL);
	array = (char **) gc_alloc((count_words(s, c) + 1) * sizeof(char *));
	if (array == NULL)
		return (NULL);
	index = 0;
	while (*s)
	{
		if (*s != c)
		{
			get_next_word(&s, c, &start);
			array[index] = (char *) gc_alloc(s - start + 1);
			if (array[index] == NULL)
				return (NULL);
			array[index] = ft_dup(array[index], start, s - start);
			index++;
		}
		else
			s++;
	}
	return (array[index] = NULL, array);
}
