/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberkass <aberkass@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 20:35:46 by aberkass          #+#    #+#             */
/*   Updated: 2025/05/22 20:35:48 by aberkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_quote(char c)
{
	return (c == '"' || c == '\'');
}

int	is_operator(char c)
{
	return (c == '|' || c == '>' || c == '<');
}

int	is_white_space(char c)
{
	return (c == ' ' || c == '\t');
}
