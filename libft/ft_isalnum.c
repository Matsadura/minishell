/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaoui <zzaoui@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 21:45:41 by zzaoui            #+#    #+#             */
/*   Updated: 2024/10/17 21:58:59 by zzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * ft_isalnum - Checks for an alphanumeric character
 * @c: The element to check
 * Return: 1 if True, 0 otherwise
 */
int	ft_isalnum(int c)
{
	int	result;

	result = ft_isalpha(c) || ft_isdigit(c);
	return (result);
}
