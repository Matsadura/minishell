/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expander.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberkass <aberkass@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 15:00:00 by aberkass          #+#    #+#             */
/*   Updated: 2025/06/15 15:00:00 by aberkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * find_var_end - finds the end of a variable name in heredoc
 * @str: string starting after the $
 * return: length of the variable name
 */
static int	find_var_end(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '?')
		return (1);
	if (ft_isdigit(str[0]) == 0 && str[0] != '_' && ft_isalpha(str[0]) == 0)
		return (0);
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	return (i);
}

/**
 * get_var_value - gets the value of a variable for heredoc expansion
 * @var_name: name of the variable
 * @env: environment variables
 * @exit_status: current exit status
 * return: variable value or empty string if not found
 */
static char	*get_value(char *var_name, char **env, int exit_status)
{	char	*value;
	char	*exit_str;

	if (ft_strcmp(var_name, "?") == 0)
	{
		exit_str = ft_itoa(exit_status);
		return (exit_str);
	}
	value = get_env(env, var_name);
	if (value == NULL)
		return (gc_strldup("", 0));
	return (gc_strldup(value, ft_strlen(value)));
}

/**
 * expand_variable - expands a single variable in heredoc line
 * @result: current result string
 * @line: original line
 * @pos: position in line (will be updated)
 * @env: environment variables
 * @exit_status: current exit status
 * return: new result string with variable expanded
 */
static char	*expand_variable(char *result, char *line, int *pos, 
	char **env, int exit_status)
{
	int		var_len;
	char	*var_name;
	char	*var_value;
	char	*new_result;

	(*pos)++;
	var_len = find_var_end(line + *pos);
	if (var_len == 0)
		return (append_char_to_str(result, '$'));
	var_name = gc_strldup(line + *pos, var_len);
	if (var_name == NULL)
		return (result);
	var_value = get_value(var_name, env, exit_status);
	if (var_value == NULL)
		return (result);
	new_result = gc_strljoin(result, var_value, ft_strlen(var_value));
	*pos += var_len;
	return (new_result);
}

/**
 * expand_heredoc_line - expands variables in a heredoc line
 * @line: line to expand
 * @env: environment variables
 * @exit_status: current exit status
 * return: expanded line
 */
char	*expand_heredoc_line(char *line, char **env, int exit_status)
{
	char	*result;
	int		pos;

	result = gc_strldup("", 0);
	if (result == NULL)
		return (NULL);
	pos = 0;
	while (line[pos])
	{
		if (line[pos] == '$')
			result = expand_variable(result, line, &pos, env, exit_status);
		else
		{
			result = append_char_to_str(result, line[pos]);
			pos++;
		}
		if (result == NULL)
			return (NULL);
	}
	return (result);
}
