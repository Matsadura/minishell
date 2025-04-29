/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaoui <zzaoui@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 19:21:49 by zzaoui            #+#    #+#             */
/*   Updated: 2024/11/04 18:05:15 by zzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * ft_lstclear - Deletes and frees the given node and every
 *		successor of that node using the function 'del' and free
 *		Finally the pointer to the list must be set to NULL
 * @lst: The address of a pointer to a node
 * @del: The address of the function used to delete the content
 *		of the node
 */
void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*current;
	t_list	*tmp;

	if (*lst == NULL || del == NULL)
		return ;
	current = *lst;
	while (current)
	{
		del(current->content);
		tmp = current;
		current = current->next;
		free(tmp);
	}
	*lst = NULL;
}
