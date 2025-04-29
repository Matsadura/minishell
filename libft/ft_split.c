/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaoui <zzaoui@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 13:59:37 by zzaoui            #+#    #+#             */
/*   Updated: 2024/11/03 21:51:38 by zzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * count_words -
 * @str:
 * @c:
 * Return:
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
 * free_array -
 */
static void	free_array(char **array, int last_index)
{
	while (last_index >= 0)
	{
		free(array[last_index]);
		last_index--;
	}
	free(array);
}

/**
 * ft_split - Splits a string  into multiple strings using
 *		the character a delimiter
 * @s: the string to split
 * @c: the delimiter character
 */
char	**ft_split(char const *s, char c)
{
	int		index;
	char	**array;
	char	*start;

	if (s == NULL)
		return (NULL);
	array = (char **) malloc((count_words(s, c) + 1) * sizeof(char *));
	if (array == NULL)
		return (NULL);
	index = 0;
	while (*s)
	{
		if (*s != c)
		{
			get_next_word(&s, c, &start);
			array[index] = (char *) malloc(s - start + 1);
			if (array[index] == NULL)
				return (free_array(array, index - 1), NULL);
			array[index] = ft_dup(array[index], start, s - start);
			index++;
		}
		else
			s++;
	}
	return (array[index] = NULL, array);
}
