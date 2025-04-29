/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaoui <zzaoui@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 11:28:26 by zzaoui            #+#    #+#             */
/*   Updated: 2025/01/26 21:39:48 by zzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif /* BUFFER_SIZE */
# ifndef FD_SETSIZE
#  define FD_SETSIZE 1024
# endif /* FD_SETSIZE */
# define MAX_FD FD_SETSIZE

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>

char	*get_next_line(int fd);
char	*ft_strndup(char *buff, int start, int finish);
char	*ft_find_line(char **buff);
char	*ft_strjoin_gnl(char *s1, char const *s2);
size_t	ft_strlen_gnl(const char *str);

#endif /* GET_NEXT_LINE_BONUS_H */
