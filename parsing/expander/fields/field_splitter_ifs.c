/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   field_splitter_ifs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberkass <aberkass@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 00:15:16 by aberkass          #+#    #+#             */
/*   Updated: 2025/06/21 08:37:05 by aberkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/**
 * handle_empty_ifs - handle the case when IFS is empty
 * @s: the string to return as single field
 * return: array containing single string or NULL on failure
 */
static char	**handle_empty_ifs(char const *s)
{
	char	**result;

	result = (char **)gc_alloc(2 * sizeof(char *));
	if (result == NULL)
		return (NULL);
	result[0] = gc_strdup(s);
	if (result[0] == NULL)
	{
		gc_free(result);
		return (NULL);
	}
	result[1] = NULL;
	return (result);
}

/**
 * wc_ifs - count numbers of word in a string using IFS
 * @s: the string to count words in
 * @ifs: IFS set containing seperator chars
 * return: number of words that could result by ifs splitting
 */
static int	wc_ifs(char const *s, char *ifs)
{
	int	wc;
	int	i;

	if (s == NULL || ifs == NULL || ifs[0] == '\0')
		return (1);
	wc = 0;
	i = 0;
	while (s[i] != '\0')
	{
		while (is_ifs_char(s[i], ifs) == 1
			&& s[i] != '\0')
			i++;
		if (is_ifs_char(s[i], ifs) == 0
			&& s[i] != '\0')
		{
			wc++;
			while (is_ifs_char(s[i], ifs) == 0
				&& s[i] != '\0')
				i++;
		}
	}
	return (wc);
}

/**
 * split_words - split string into words based on IFS characters
 * @s: string to split
 * @ifs: IFS characters set
 * @word_count: number of words to allocate for
 * return: array of split words or NULL on failure
 */
static char	**split_words(char const *s, char *ifs, int word_count)
{
	char	**splited;
	size_t	start;
	int		i;
	int		j;

	splited = (char **)gc_alloc((word_count + 1) * sizeof(char *));
	if (splited == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s[j] != '\0' && i < word_count)
	{
		while (is_ifs_char(s[j], ifs) == 1
			&& s[j] != '\0')
			j++;
		start = j;
		while (is_ifs_char(s[j], ifs) == 0
			&& s[j] != '\0')
			j++;
		splited[i] = gc_substr(s, start, j - start);
		if (splited[i] == NULL)
			return (free_fields_array(splited), NULL);
		i++;
	}
	splited[i] = NULL;
	return (splited);
}

/**
 * split_by_ifs - split string into fields based on IFS characters
 * @s: string to split
 * @ifs: IFS characters set
 * return: array of field strings or NULL on failure
 */
char	**split_by_ifs(char const *s, char *ifs)
{
	int	word_count;

	if (s == NULL || ifs == NULL)
		return (NULL);
	if (ifs[0] == '\0')
		return (handle_empty_ifs(s));
	word_count = wc_ifs(s, ifs);
	return (split_words(s, ifs, word_count));
}
