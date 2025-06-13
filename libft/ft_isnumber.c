/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnumber.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaoui <zzaoui@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 15:20:38 by zzaoui            #+#    #+#             */
/*   Updated: 2025/05/30 15:20:41 by zzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * ft_isnumber - Checks if arg is a number
 * @arg: The element to check
 * Return: 1 if true, 0 otherwise
 */
int	ft_isnumber(char *arg)
{
	int	i;

	if (arg == NULL || *arg == '\0')
		return (0);
	i = 0;
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	while (arg[i])
	{
		if (ft_isdigit(arg[i]) != 1)
			return (0);
		i++;
	}
	return (1);
}
