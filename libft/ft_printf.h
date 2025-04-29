/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaoui <zzaoui@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 19:18:17 by zzaoui            #+#    #+#             */
/*   Updated: 2025/01/25 11:58:39 by zzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>
# include <stddef.h>
# include <stdlib.h>
# include <limits.h>
# include <unistd.h>
# include <stdint.h>

typedef struct s_spec
{
	char	spec;
	int		(*f)(va_list, int);
}	t_spec;

int		ft_printf(const char *str, ...);
int		ft_dprintf(int fd, const char *str, ...);

/* Structure related functions */
int		init(t_spec **spec);
int		get_spec_func(char s, t_spec *sp, va_list arg, int fd);

/* Specificer functions */
int		put_mod(va_list arg, int fd);
int		put_char(va_list arg, int fd);
int		put_str(va_list arg, int fd);
int		put_nbr(va_list arg, int fd);
int		put_unbr(va_list arg, int fd);
int		put_xlower(va_list arg, int fd);
int		put_xupper(va_list arg, int fd);
int		put_p(va_list arg, int fd);

#endif /* FT_PRINTF_H */
