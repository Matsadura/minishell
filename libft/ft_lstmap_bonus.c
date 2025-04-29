/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaoui <zzaoui@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 01:56:51 by zzaoui            #+#    #+#             */
/*   Updated: 2024/11/04 18:49:17 by zzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * ft_lstmap - Iterates the list 'lst' and applies
 *		the function 'f' on the content of each node.
 *		Creates a new list resulting of the successive
 *		applications of the function 'f'. The 'del' function
 *		is used to delete the content of a node if needed.
 * @lst: The address of a pointer to a node
 * @f: The address of the function usde to iterate on the list.
 * @del: The address of the function used to delte the content
 *		of a node if needed.
 * Return: The new list, NULL if the allocation fails.
 */
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*head;
	t_list	*current;
	void	*tmp;

	if (lst == NULL || f == NULL || del == NULL)
		return (NULL);
	head = NULL;
	current = lst;
	while (current)
	{
		tmp = f(current->content);
		new = ft_lstnew(tmp);
		if (new == NULL)
		{
			free(tmp);
			ft_lstclear(&head, del);
			return (NULL);
		}
		new->next = new->next;
		ft_lstadd_back(&head, new);
		current = current->next;
	}
	return (head);
}
