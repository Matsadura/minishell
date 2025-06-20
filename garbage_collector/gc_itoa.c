/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberkass <aberkass@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 12:00:16 by aberkass          #+#    #+#             */
/*   Updated: 2025/06/01 23:27:27 by aberkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc_header.h"

static int	ft_nlen(int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static void	ft_fill(char *res, int n, int i)
{
	while (n > 0)
	{
		res[i] = (n % 10) + 48;
		n /= 10;
		i--;
	}
}

char	*gc_itoa(int n)
{
	char		*res;
	int			len;
	int			s;

	s = 0;
	if (n == -2147483648)
		return (gc_strldup("-2147483648", ft_strlen("-2147483648")));
	if (n < 0)
	{
		s++;
		n *= -1;
	}
	len = ft_nlen(n);
	res = gc_alloc((len + s + 1) * sizeof(char));
	if (res == NULL)
		return (NULL);
	if (s != 0)
		res[0] = '-';
	if (n == 0)
		res[0] = '0';
	ft_fill(res, n, len + s - 1);
	res[len + s] = '\0';
	return (res);
}
