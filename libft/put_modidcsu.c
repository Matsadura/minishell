/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_%idsu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaoui <zzaoui@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 21:36:09 by zzaoui            #+#    #+#             */
/*   Updated: 2024/11/30 17:39:15 by zzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/**
 * put_mod - prints a modulo
 * @arg: argument to print (from va_list)
 * @fd: the file descriptor to write in
 * Return: the number of written bytes
 */
int	put_mod(va_list arg, int fd)
{
	(void) arg;
	return (write(fd, "%", 1));
}

/**
 * putc - prints a character
 * @arg: character to print (from va_list)
 * @fd: the file descriptor to write in
 * Return: the number of written bytes
 */
int	put_char(va_list arg, int fd)
{
	char	c;

	c = (char)va_arg(arg, int);
	return (write(fd, &c, 1));
}

/**
 * put_str - prints a string
 * @arg: string to print (from va_list)
 * @fd: the file descriptor to write in
 * Return: The number of written bytes
 */
int	put_str(va_list arg, int fd)
{
	char	*str;

	str = va_arg(arg, char *);
	if (str == NULL)
		return (write(fd, "(null)", 6));
	return (write(fd, str, ft_strlen(str)));
}

/**
 * put_nbr - prints a number
 * @arg: number to print (from va_list)
 * @fd: the file descriptor to write in
 * Return: the number of written bytes
 */
int	put_nbr(va_list arg, int fd)
{
	char	*n;
	int		written;

	n = ft_itoa(va_arg(arg, int));
	written = write(fd, n, ft_strlen(n));
	if (n != NULL)
		free(n);
	return (written);
}

/**
 * put_nbr - prints an unsigned number
 * @arg: unsigned number to print (from va_list)
 * @fd: the file descriptor to write in
 * Return: the number of written bytes
 */
int	put_unbr(va_list arg, int fd)
{
	char			buff[12];
	unsigned int	n;
	unsigned int	m;
	int				i;

	n = va_arg(arg, unsigned int);
	i = 0;
	if (n == 0)
		return (write(fd, "0", 1));
	m = 1;
	while (n / m >= 10)
		m *= 10;
	while (m >= 1)
	{
		buff[i++] = ((n / m) % 10) + '0';
		m /= 10;
	}
	buff[i] = '\0';
	return (write(fd, &buff, ft_strlen(buff)));
}
