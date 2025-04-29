/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaoui <zzaoui@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 18:57:27 by zzaoui            #+#    #+#             */
/*   Updated: 2024/11/11 19:24:09 by zzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * ft_memmove - copy byte string
 * @dst: the string to copy to
 * @src: the string to copy from
 * Return: the originql vqlue of dst
 */
void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;
	char	*tmp1;
	char	*tmp2;

	if (dst == NULL && src == NULL)
		return (dst);
	if (dst == src)
		return (dst);
	tmp1 = (char *) dst;
	tmp2 = (char *) src;
	if (tmp1 > tmp2)
	{
		while (len-- > 0)
			tmp1[len] = tmp2[len];
	}
	else
	{
		i = 0;
		while (i < len)
		{
			tmp1[i] = tmp2[i];
			i++;
		}
	}
	return (dst);
}
