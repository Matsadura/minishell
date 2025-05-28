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

int	handle_single_quotes(char **res, int i, t_exp_context *cntx)
{
	if (cntx->state == SINGLE_QUOTES)
		cntx->state = NORMAL;
	else if (cntx->state == NORMAL)
		cntx->state = SINGLE_QUOTES;
	return (i + 1);
}

int	handle_double_quotes(char **res, int i, t_exp_context *cntx)
{
	if (cntx->state == DOUBLE_QUOTES)
		cntx->state = NORMAL;
	else if (cntx->state == NORMAL)
		cntx->state = DOUBLE_QUOTES;
	return (i + 1);
}

int	handle_regular_character(char *token, char **res, int i)
{
	*res = append_char_to_str(*res, token[i]);
	return (i + 1);
}

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
