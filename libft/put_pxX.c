/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pxX.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaoui <zzaoui@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 17:46:46 by zzaoui            #+#    #+#             */
/*   Updated: 2024/12/01 16:44:35 by zzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/**
 * put_x - Prints a number in hexadecimal
 *	lowercase format
 * @arg: the number to print (from va_list)
 * @fd: the file descriptor to write in
 * Return: the number of writter bytes
 */
int	put_xlower(va_list arg, int fd)
{
	char			buff[12];
	char			*base;
	int				i;

	unsigned int (n), (m);
	base = "0123456789abcdef";
	i = 0;
	n = va_arg(arg, unsigned int);
	if (n == 0)
		return (write(fd, "0", 1));
	m = 1;
	while (n / m >= 16)
		m *= 16;
	while (m >= 1)
	{
		buff[i++] = base[(n / m) % 16];
		m /= 16;
	}
	buff[i] = '\0';
	return (write(fd, &buff, ft_strlen(buff)));
}

/**
 * put_X - Prints a number in hexadecimal
 *	uppercase format
 * @arg: the number to print (from va_list)
 * @fd: the file descriptor to write in
 * Return: the number of writter bytes
 */
int	put_xupper(va_list arg, int fd)
{
	char			buff[12];
	char			*base;
	int				i;

	unsigned int (m), (n);
	base = "0123456789ABCDEF";
	i = 0;
	n = va_arg(arg, unsigned int);
	if (n == 0)
		return (write(fd, "0", 1));
	m = 1;
	while (n / m >= 16)
		m *= 16;
	while (m >= 1)
	{
		buff[i++] = base[(n / m) % 16];
		m /= 16;
	}
	buff[i] = '\0';
	return (write(fd, &buff, ft_strlen(buff)));
}

/**
 * put_p - prints the address in hexadecimal format
 * @arg: the address to print (from va_list)
 * @fd: the file descriptor to write in
 * Return: the number of written bytes
 */
int	put_p(va_list arg, int fd)
{
	char			buff[16];
	char			*base;

	unsigned long int (n), (m), (i);
	base = "0123456789abcdef";
	i = 0;
	n = va_arg(arg, unsigned long int);
	if (n == 0)
		return (write(fd, "(nil)", ft_strlen("(nil)")));
	m = 1;
	while (n / m >= 16)
		m *= 16;
	while (m >= 1)
	{
		buff[i++] = base[(n / m) % 16];
		m /= 16;
	}
	buff[i] = '\0';
	write(1, "0x", 2);
	return (write(fd, &buff, ft_strlen(buff)) + 2);
}
