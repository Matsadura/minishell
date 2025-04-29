/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaoui <zzaoui@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 16:53:05 by zzaoui            #+#    #+#             */
/*   Updated: 2024/11/02 17:01:32 by zzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * ft_lstsize - Counts the number of nodes in a list
 * @lst: The beginning of the list
 * Return: The length of the list
 */
int	ft_lstsize(t_list *lst)
{
	int		len;
	t_list	*current;

	len = 0;
	if (lst == NULL)
		return (len);
	current = lst;
	while (current)
	{
		current = current->next;
		len++;
	}
	return (len);
}
