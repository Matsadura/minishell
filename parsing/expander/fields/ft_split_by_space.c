/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_by_space.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberkass <aberkass@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 08:08:00 by aberkass          #+#    #+#             */
/*   Updated: 2024/06/01 22:18:06 by aberkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

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

static void	ft_free(char **s, int i)
{
	while (i > 0)
	{
		free(s[--i]);
	}
	free(s);
}

char	**ft_split_by_space(char const	*s)
{
	char		**splited;
	int			i;
	int			j;
	size_t		start;

	splited = (char **)malloc((ft_wc(s) + 1) * sizeof(char *));
	if (!splited || !s)
		return (free(splited), NULL);
	i = 0;
	j = 0;
	while (s[j] && i < ft_wc(s))
	{
		while ((s[j] == ' ' || s[j] == '\t') && s[j])
			j++;
		start = j;
		while (s[j] != ' ' && s[j] != '\t' && s[j])
			j++;
		splited[i++] = ft_substr(s, start, j - start);
		if (!splited[i - 1])
			return (ft_free(splited, i - 1), NULL);
	}
	splited[i] = NULL;
	return (splited);
}
