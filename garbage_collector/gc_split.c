#include "gc_header.h"

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
