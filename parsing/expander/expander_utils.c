/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberkass <aberkass@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 17:50:10 by aberkass          #+#    #+#             */
/*   Updated: 2025/05/28 18:07:19 by aberkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * handle_single_quotes - manages single quote state transitions
 * @i: current character index
 * @cntx: expansion context to update the quote state
 * return: next index position (i + 1)
 */
int	handle_single_quotes(int i, t_exp_context *cntx)
{
	if (cntx->state == SINGLE_QUOTES)
		cntx->state = NORMAL;
	else if (cntx->state == NORMAL)
		cntx->state = SINGLE_QUOTES;
	return (i + 1);
}

/**
 * handle_double_quotes - manages double quote state transitions
 * @i: current character index
 * @cntx: expansion context to update the quote state
 * return: next index position (i + 1)
 */
int	handle_double_quotes(int i, t_exp_context *cntx)
{
	if (cntx->state == DOUBLE_QUOTES)
		cntx->state = NORMAL;
	else if (cntx->state == NORMAL)
		cntx->state = DOUBLE_QUOTES;
	return (i + 1);
}

/**
 * handle_regular_character - processes non-special characters
 * @token: the token value
 * @res: pointer to the result string
 * @i: current character index
 * return: next index position (i + 1)
 */
int	handle_regular_character(char *token, char **res, int i)
{
	*res = append_char_to_str(*res, token[i]);
	return (i + 1);
}

/**
 * append_char_to_str - appends a single character to a string
 * @str: the source string to append to
 * @c: the character to append
 * return: new string with character appended or NULL on allocation failure
 */
char	*append_char_to_str(const char *str, char c)
{
	int		len;
	int		i;
	char	*new_str;

	len = ft_strlen(str);
	new_str = gc_alloc(len + 2);
	if (new_str == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[len] = c;
	new_str[len + 1] = '\0';
	return (new_str);
}

/**
 * append_str_to_str - concatenates two strings into a new string
 * @dst: the destination string
 * @src: the source string to append
 * return: new concatenated string, or dst on allocation failure
 */
char	*append_str_to_str(char *dst, const char *src)
{
	char	*new_str;
	int		src_len;
	int		dst_len;
	int		i;
	int		j;

	src_len = ft_strlen(src);
	dst_len = ft_strlen(dst);
	new_str = gc_alloc(src_len + dst_len + 1);
	if (new_str == NULL)
		return (dst);
	i = 0;
	while (i < dst_len)
	{
		new_str[i] = dst[i];
		i++;
	}
	j = 0;
	while (j < src_len)
	{
		new_str[i + j] = src[j];
		j++;
	}
	new_str[dst_len + src_len] = '\0';
	return (new_str);
}
