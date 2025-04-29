/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specifier.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaoui <zzaoui@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 20:53:45 by zzaoui            #+#    #+#             */
/*   Updated: 2024/11/30 21:20:53 by zzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/**
 * init - Initializes the spec array
 */
int	init(t_spec **spec)
{
	static t_spec	sp[] = {
	{'%', put_mod},
	{'c', put_char},
	{'s', put_str},
	{'d', put_nbr},
	{'i', put_nbr},
	{'u', put_unbr},
	{'x', put_xlower},
	{'X', put_xupper},
	{'p', put_p},
	{'\0', NULL}
	};

	*spec = sp;
	return (1337);
}

/**
 * get_spec_func - selects the correct function
 *	to perform the operation asked by the user
 * @s: the format specifier
 * @sp: the array of structs the contains {specifier, function}
 * 	collection
 * @fd: the file descriptor to write in
 * Return: the number of written bytes
 */
int	get_spec_func(char s, t_spec *sp, va_list arg, int fd)
{
	int	i;

	i = 0;
	while (sp[i].spec != '\0')
	{
		if (sp[i].spec == s)
			return (sp[i].f(arg, fd));
		i++;
	}
	return (write(fd, &s, 1));
}
