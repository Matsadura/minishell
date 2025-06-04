/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_splitter.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberkass <aberkass@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 12:08:00 by aberkass          #+#    #+#             */
/*   Updated: 2024/06/01 22:18:06 by aberkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/**
 * ft_wc - counts the number of words in a string separated by spaces/tabs
 * @s: the input string to count words in
 * return: number of words found in the string
 */
static int	ft_wc(char const *s)
{
	int	wc;
	int	i;

	wc = 0;
	i = 0;
	while (s[i])
	{
		while ((s[i] == ' ' || s[i] == '\t') && s[i])
			i++;
		if (s[i] != ' ' && s[i] != '\t' && s[i])
		{
			wc++;
			while (s[i] != ' ' && s[i] != '\t' && s[i])
				i++;
		}
	}
	return (wc);
}

/**
 * ft_free - frees a partially allocated string array and its elements
 * @s: the string array to free
 * @i: number of elements that were successfully allocated
 */
static void	ft_free(char **s, int i)
{
	while (i > 0)
	{
		gc_free(s[--i]);
	}
	gc_free(s);
}

/**
 * ft_split_by_space - splits a string into an array of words by whitespace
 * @s: the input string to split
 * return: array of word strings or NULL on failure
 */
char	**ft_split_by_space(char const	*s)
{
	char		**splited;
	int			i;
	int			j;
	size_t		start;

	splited = (char **)gc_alloc((ft_wc(s) + 1) * sizeof(char *));
	if (!splited || !s)
		return (gc_free(splited), NULL);
	i = 0;
	j = 0;
	while (s[j] && i < ft_wc(s))
	{
		while ((s[j] == ' ' || s[j] == '\t') && s[j])
			j++;
		start = j;
		while (s[j] != ' ' && s[j] != '\t' && s[j])
			j++;
		splited[i++] = gc_substr(s, start, j - start);
		if (!splited[i - 1])
			return (ft_free(splited, i - 1), NULL);
	}
	splited[i] = NULL;
	return (splited);
}
