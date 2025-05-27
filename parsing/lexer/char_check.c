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

/**
 * is_quote - checks if the character is a quote
 * @c: the character to check
 * return: 1 if character is a quote 0 if it's not
 */
int	is_quote(char c)
{
	return (c == '"' || c == '\'');
}

/**
 * is_operator - checks if the character is an operator
 * @c: the character to check
 * return: 1 if character is an operator (|, >, <) or 0 if it's not
 */
int	is_operator(char c)
{
	return (c == '|' || c == '>' || c == '<');
}

/**
 * is_white_space - checks if the character is whitespace
 * @c: the character to check
 * Return: 1 if character is space or tab 0 if it's not
 */
int	is_white_space(char c)
{
	return (c == ' ' || c == '\t');
}
