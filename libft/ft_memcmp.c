/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaoui <zzaoui@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 11:02:52 by zzaoui            #+#    #+#             */
/*   Updated: 2024/10/25 11:45:53 by zzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * ft_memcmp - compare byte string
 * @s1: first byte string
 * @s2: second byte string
 * @n: the mqx length
 * Return: 0 if the two strings are identical,
 *	otherwise the difference between the first
 *	two differing bytes
 */
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*tmp1;
	unsigned char	*tmp2;
	size_t			i;

	tmp1 = (unsigned char *) s1;
	tmp2 = (unsigned char *) s2;
	i = 0;
	while (i < n && tmp1[i] == tmp2[i])
		i++;
	if (i == n)
		return (0);
	return (tmp1[i] - tmp2[i]);
}
