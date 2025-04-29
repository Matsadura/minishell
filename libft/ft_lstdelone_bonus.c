/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaoui <zzaoui@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 18:13:36 by zzaoui            #+#    #+#             */
/*   Updated: 2024/11/02 18:49:32 by zzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * ft_lstdelone - Takes a a parameter a node and frees
 *		the memory of the node's content using the function
 *		'del' givem a parameter and free the node.
 *		the memory of 'next' must not be freed.
 * @lst: The node to free
 * @del: The address of the function used to delete the content
 */
void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (lst == NULL || del == NULL)
		return ;
	del(lst->content);
	free(lst);
}
