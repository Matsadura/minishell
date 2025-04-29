/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaoui <zzaoui@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 11:27:26 by zzaoui            #+#    #+#             */
/*   Updated: 2025/02/05 16:47:49 by zzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

/**
 * nl_in - Check for new line character
 * @str: The str to check in
 * Return: 1 if found, otherwise 0
 */
int	nl_in(char *str)
{
	int	i;

	if (str == NULL)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

/**
 * check_read_error - Checks the read syscall
 * @count_read: number of bytes read
 * @read_buff: the buffer of read
 * @buff: the static buffer
 * return: -1 in case of error, otherwise 0
 */
int	check_read_error(int count_read, char **read_buff, char **buff)
{
	if (count_read < 0)
	{
		free(*buff);
		*buff = NULL;
		free(*read_buff);
		*read_buff = NULL;
		return (-1);
	}
	return (0);
}

/**
 * handle_buffer - Handles static buffer and read buffer operations
 * @buff: the static buffer that contains the rest of the lines
 * @read_buff: the buffer the read syscall appends fills
 * @count_read: the count of bytes read
 * @fd: the file descriptor
 * Return: the new static buffer
 */
char	*handle_buffer(char **buff, char **read_buff, int count_read, int fd)
{
	char	*tmp;

	count_read = 1;
	while (nl_in(*buff) == 0 && count_read > 0)
	{
		count_read = read(fd, *read_buff, BUFFER_SIZE);
		if (check_read_error(count_read, read_buff, buff) == -1)
			return (NULL);
		if (count_read == 0)
			break ;
		(*read_buff)[count_read] = '\0';
		tmp = ft_strjoin_gnl(*buff, *read_buff);
		if (tmp == NULL)
		{
			free(*read_buff);
			free(*buff);
			*buff = NULL;
			*read_buff = NULL;
			return (NULL);
		}
		*buff = tmp;
	}
	return (*buff);
}

/**
 * get_next_line - Gets the next line
 * @fd: the file descriptor to read from
 * Return: the line
 */
char	*get_next_line(int fd)
{
	static char	*buffers;
	char		*read_buff;
	char		*line;
	int			count_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	read_buff = malloc(BUFFER_SIZE + 1);
	if (read_buff == NULL)
		return (NULL);
	count_read = 1;
	if (handle_buffer(&buffers, &read_buff, count_read, fd) == NULL)
	{
		free(read_buff);
		return (NULL);
	}
	line = ft_find_line(&buffers);
	if (line == NULL || buffers[0] == '\0')
	{
		free(buffers);
		buffers = NULL;
	}
	free(read_buff);
	return (line);
}
