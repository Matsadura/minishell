/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaoui <zzaoui@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 23:04:48 by zzaoui            #+#    #+#             */
/*   Updated: 2024/10/17 23:15:21 by zzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * ft_isprint - Checks for any printable character
 *	including space
 * @c: The character to check
 * Return: 1 if True, otherwise 0.
 */
int	ft_isprint(int c)
{
	if (32 <= c && c < 127)
		return (1);
	return (0);
}
