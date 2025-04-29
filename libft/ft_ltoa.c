/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaoui <zzaoui@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 17:41:17 by zzaoui            #+#    #+#             */
/*   Updated: 2025/01/28 17:41:34 by zzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * ft_ltoa - Allocates and returns a string reprresenting
 *		a long integer received as argument.
 * @n: the long integer to convert
 * Return: the string representing the integer, NULL otherwise.
 */
char	*ft_ltoa(long n)
{
	char			buff[12];
	unsigned long	m;
	long			i;

	i = 0;
	if (n == 0)
		return (ft_strdup("0"));
	if (n < 0)
	{
		buff[i++] = '-';
		n = (unsigned long) -n;
	}
	m = 1;
	while (n / m >= 10)
		m *= 10;
	while (m >= 1)
	{
		buff[i++] = ((n / m) % 10) + '0';
		m /= 10;
	}
	buff[i] = '\0';
	return (ft_strdup(buff));
}
