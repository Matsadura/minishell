/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaoui <zzaoui@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 12:45:47 by zzaoui            #+#    #+#             */
/*   Updated: 2024/11/04 15:46:45 by zzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * ft_putnbr_fd - Outputs the integer 'n' to the given
 *		file descriptor
 * @n: the integer to output
 * @fd: the fild descriptor on which to write
 */
void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	m;

	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n = (unsigned int) -n;
	}
	m = 1;
	while (n / m >= 10)
		m *= 10;
	while (m >= 1)
	{
		ft_putchar_fd((n / m) % 10 + '0', fd);
		m /= 10;
	}
}
