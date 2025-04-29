/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaoui <zzaoui@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 01:22:43 by zzaoui            #+#    #+#             */
/*   Updated: 2024/11/03 01:53:24 by zzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * ft_lstiter - Iterates the list 'lst' and applies
 *		the function 'f' on the content of each node
 * @lst: The address of a pointer to a node
 * @f: The address of the function used to iterate on
 *		the list
 */
void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*current;

	if (lst == NULL || f == NULL)
		return ;
	current = lst;
	while (current)
	{
		f(current->content);
		current = current->next;
	}
}
