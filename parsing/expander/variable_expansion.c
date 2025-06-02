/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberkass <aberkass@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 18:07:16 by aberkass          #+#    #+#             */
/*   Updated: 2025/05/28 18:07:19 by aberkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * handle_var_expansion - handles variable expansion when $ is encountered
 * @token: the input token string being processed
 * @res: pointer to the result string 
 * @i: current index in the token string
 * @cntx: expansion context containing state and environment information
 * return: new index position after processing the variable
 */
int	handle_var_expansion(char *token, char **res, int i, t_exp_context *cntx)
{
	int		new_indx;
	char	*var_name;
	char	*var_value;

	new_indx = i;
	var_name = extract_variable_name(token, &new_indx);
	if (var_name != NULL)
	{
		var_value = get_var_value(var_name, cntx);
		if (var_value != NULL)
			*res = append_str_to_str(*res, var_value);
		return (new_indx);
	}
	else
	{
		*res = append_char_to_str(*res, '$');
		return (i + 1);
	}
}

/**
 * extract_variable_name - extracts a valid variable name from the token
 * @token: the input token string
 * @indx: pointer to current index will be updated to position after var name
 * return: extracted variable name string or NULL if invalid
 */
char	*extract_variable_name(char *token, int *indx)
{
	int	start;
	int	len;

	(*indx)++;
	if (token[*indx] != '\0' && token[*indx] == '?')
	{
		(*indx)++;
		return (gc_strldup("?", 1));
	}
	if (ft_isalpha(token[*indx]) == 0 && token[*indx] != '_')
		return (NULL);
	start = *indx;
	while (token[*indx] && (ft_isalnum(token[*indx]) || token[*indx] == '_'))
		(*indx)++;
	len = *indx - start;
	if (len == 0)
		return (NULL);
	return (gc_strldup(token + start, len));
}

/**
 * get_var_value - retrieves the value of a variable from the environment
 * @var_name: the name of the variable to get
 * @cntx: expansion context containing environment and state information
 * return: variable value string, or empty string if not found
 */
char	*get_var_value(char *var_name, t_exp_context *cntx)
{
	size_t	name_len;
	int		i;
	char	*env_line;

	if (ft_strncmp(var_name, "?", 1) == 0)
		return (ft_itoa(cntx->last_exit_status));
	if (cntx->env == NULL)
		return (gc_strldup("", 0));
	name_len = ft_strlen(var_name);
	i = 0;
	while (cntx->env[i])
	{
		env_line = cntx->env[i];
		if (ft_strncmp(env_line, var_name, name_len) == 0
			&& env_line[name_len] == '=')
			return (gc_strldup(env_line + name_len + 1,
					ft_strlen(env_line + name_len + 1)));
		i++;
	}
	return (gc_strldup("", 0));
}
