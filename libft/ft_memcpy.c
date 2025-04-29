/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaoui <zzaoui@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 16:30:09 by zzaoui            #+#    #+#             */
/*   Updated: 2024/11/11 19:23:05 by zzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * ft_memcpy - copy memory area
 * @dst: the memory area to copy to
 * @src: the memory area to copy from
 * @n: the number of bytes to copy
 */
void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*tmp1;
	unsigned char	*tmp2;
	size_t			i;

	if (dst == NULL && src == NULL)
		return (dst);
	if (dst == src)
		return (dst);
	tmp1 = (unsigned char *) dst;
	tmp2 = (unsigned char *) src;
	i = 0;
	while (i < n)
	{
		tmp1[i] = tmp2[i];
		i++;
	}
	return (dst);
}
