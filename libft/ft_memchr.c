/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaoui <zzaoui@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 10:05:51 by zzaoui            #+#    #+#             */
/*   Updated: 2024/10/25 11:01:27 by zzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * ft_memchr - locate byte in byte string
 * @s: The string to search in
 * @c: the byte to locate
 * @n: the limit of the search radius
 * Return: a pointer to the byte located
 * 	or NULL if not such byte exists whitin
 * 	n bytes
 */
void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*tmp;
	size_t			i;

	tmp = (unsigned char *) s;
	i = 0;
	while (i < n)
	{
		if (tmp[i] == (unsigned char) c)
			return (tmp + i);
		i++;
	}
	return (NULL);
}
