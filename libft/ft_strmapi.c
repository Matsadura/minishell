/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaoui <zzaoui@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 17:21:12 by zzaoui            #+#    #+#             */
/*   Updated: 2024/11/01 11:20:40 by zzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * ft_strmapi - Applies the function 'f' to each character
 *		of the string 's', and passing its index as first argument
 *		to create a new string resulting from successive apprilations
 *		of 'f'
 * @s: the string on which to iterate
 * @f: the function to apply to each character
 * Return: the string created from successive applications of 'f'
 * 		or NULL if the allocation fails
 */
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char				*str;
	unsigned int		i;

	if (s == NULL || f == NULL)
		return (NULL);
	str = (char *) malloc(ft_strlen(s) + 1);
	if (str == NULL)
		return (NULL);
	i = 0;
	while (s[i])
	{
		str[i] = f(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}
