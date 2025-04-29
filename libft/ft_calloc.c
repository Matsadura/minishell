/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaoui <zzaoui@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:11:03 by zzaoui            #+#    #+#             */
/*   Updated: 2024/10/25 15:42:48 by zzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * ft_calloc - contigously allocates enough space for count objects
 * 		that are size byte of memory each, allocates with bytes of
 * 		value zero
 * @count: The count of objects
 * @size: the size of each object
 * Return: a pointer to the allocated memory
 */
void	*ft_calloc(size_t count, size_t size)
{
	void	*area;

	if (count && size > SIZE_MAX / count)
		return (NULL);
	area = malloc(count * size);
	if (area == NULL)
		return (NULL);
	ft_bzero(area, size * count);
	return (area);
}
