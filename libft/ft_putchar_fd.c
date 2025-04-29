/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaoui <zzaoui@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 12:17:24 by zzaoui            #+#    #+#             */
/*   Updated: 2024/11/01 12:31:11 by zzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * ft_putchar_fd - Outputs the character 'c' to the given
 *		file descriptor
 * @c: The character to output
 * @fd: The file descriptor on which to write
 */
void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
