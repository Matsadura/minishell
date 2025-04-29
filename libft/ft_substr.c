/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaoui <zzaoui@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 16:01:46 by zzaoui            #+#    #+#             */
/*   Updated: 2024/11/04 15:31:15 by zzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * ft_substr - Allocates and returns a substring from the string s
 * @s: The string from which to create the substring
 * @start: The start index of the substring in the string 's'
 * @len: The maximum length of the substring
 * Return: The substring, or NULL if allocation fails
 */
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	if (s == NULL)
		return (NULL);
	if (ft_strlen(s) == 0 || start >= ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(&s[start]))
		len = ft_strlen(&s[start]);
	str = (char *) malloc(len + 1);
	if (str == NULL)
		return (NULL);
	i = 0;
	while (i < len && s[i])
	{
		str[i] = s[start];
		i++;
		start++;
	}
	str[i] = '\0';
	return (str);
}
