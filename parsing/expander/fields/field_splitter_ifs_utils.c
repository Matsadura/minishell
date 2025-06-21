/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   field_splitter_ifs_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberkass <aberkass@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 00:15:16 by aberkass          #+#    #+#             */
/*   Updated: 2025/06/21 08:37:05 by aberkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/**
 * get_ifs_values - get IFS value from env
 * @env: environment list
 * return: IFS value, or " " as default, or empty if it was set to empty
 */
char	*get_ifs_value(char **env)
{
	char	*ifs_value;

	ifs_value = get_env(env, "IFS");
	if (ifs_value == NULL)
		return (" \t\n");
	if (ifs_value[0] == '\0')
		return ("");
	return (ifs_value);
}

/**
 * is_ifs_char - check if a character is in the IFS set
 * @c: the character to check
 * @ifs: the IFS set
 * return: 1 if the character was in the set, 0 otherwise
 */
int	is_ifs_char(char c, char *ifs)
{
	int	i;

	if (ifs == NULL)
		return (0);
	i = 0;
	while (ifs[i] != '\0')
	{
		if (ifs[i] == c)
			return (1);
		i++;
	}
	return (0);
}

/**
 * contains_ifs_character - check if a string contains IFS character
 * @str: the string to check
 * @ifs: the IFS set
 * return: 1 if the string contains IFS characters, 0 otherwise
 */
int	contains_ifs_character(char *str, char *ifs)
{
	int	i;

	if (str == NULL || ifs == NULL || ifs[0] == '\0')
		return (0);
	i = 0;
	while (str[i] != '\0')
	{
		if (is_ifs_char(str[i], ifs))
			return (1);
		i++;
	}
	return (0);
}
