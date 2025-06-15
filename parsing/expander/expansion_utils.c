/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
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
 * @cntxt: expansion context to update the quote state
 * return: next index position (i + 1)
 */
int	handle_single_quotes(int i, t_exp_context *cntxt)
{
	if (cntxt->state == SINGLE_QUOTES)
		cntxt->state = NORMAL;
	else if (cntxt->state == NORMAL)
		cntxt->state = SINGLE_QUOTES;
	return (i + 1);
}

/**
 * handle_double_quotes - manages double quote state transitions
 * @i: current character index
 * @cntxt: expansion context to update the quote state
 * return: next index position (i + 1)
 */
int	handle_double_quotes(int i, t_exp_context *cntxt)
{
	if (cntxt->state == DOUBLE_QUOTES)
		cntxt->state = NORMAL;
	else if (cntxt->state == NORMAL)
		cntxt->state = DOUBLE_QUOTES;
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
	size_t		len;
	char		*new_str;

	len = ft_strlen(str);
	new_str = gc_alloc(len + 2);
	if (new_str == NULL)
		return (NULL);
	ft_strlcpy(new_str, str, len + 2);
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
char	*append_str_to_str(char *dst, char *src)
{
	char		*new_str;
	size_t		src_len;
	size_t		dst_len;

	src_len = ft_strlen(src);
	dst_len = ft_strlen(dst);
	new_str = gc_alloc(src_len + dst_len + 1);
	if (new_str == NULL)
		return (NULL);
	ft_strlcpy(new_str, dst, dst_len + 1);
	ft_strlcat(new_str, src, src_len + dst_len + 1);
	return (new_str);
}
