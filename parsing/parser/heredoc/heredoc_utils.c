/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberkass <aberkass@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 15:00:00 by aberkass          #+#    #+#             */
/*   Updated: 2025/06/16 22:33:20 by aberkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/**
 * random_name - Generates a random temporary file name.
 * Returns: A string containing the random file name.
 */
static char	*random_name(void)
{
	static int	counter = 0;
	char		*name;
	char		*full_name;

	counter++;
	name = gc_itoa(counter);
	if (name == NULL)
		return (NULL);
	while (1)
	{
		full_name = gc_strljoin("/tmp/heredoc_", name, ft_strlen(name) + 15);
		if (full_name == NULL)
			return (NULL);
		if (access(full_name, F_OK) == -1)
			break ;
		counter++;
		name = gc_itoa(counter);
		if (name == NULL)
			return (NULL);
	}
	return (full_name);
}

/**
 * create_temp_file - Creates a temporary file for heredoc redirection.
 * Returns: The file name of the created temporary file, or NULL on failure.
 */
char	*create_temp_file(void)
{
	int		fd;
	char	*temp_file;

	temp_file = random_name();
	if (!temp_file)
		return (NULL);
	fd = open(temp_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror(temp_file);
		return (NULL);
	}
	close(fd);
	return (temp_file);
}

/**
 * remove_quotes - removes quotes from heredoc delimiter
 * @delimiter: the delimiter string to process
 * return: newly allocated string without quotes, or NULL on failure
 */
char	*remove_quotes(char *delimiter)
{
	char	*result;
	int		i;
	int		j;

	if (!delimiter)
		return (NULL);
	result = gc_alloc(ft_strlen(delimiter) + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (delimiter[i])
	{
		if (delimiter[i] != '\'' && delimiter[i] != '"')
		{
			result[j] = delimiter[i];
			j++;
		}
		i++;
	}
	result[j] = '\0';
	return (result);
}

/**
 * should_expand_heredoc - determines if heredoc delimiter should be expanded
 * @delimiter: the delimiter string to check
 * return: 1 if should expand, 0 if literal (quoted delimiter)
 */
int	should_expand_heredoc(char *delimiter)
{
	int	i;

	i = 0;
	while (delimiter[i])
	{
		if (delimiter[i] == '\'' || delimiter[i] == '"')
			return (0);
		i++;
	}
	return (1);
}

/**
 * handle_readline_eof - handles EOF condition during readline
 * @clean_delimiter: the delimiter we were expecting
 */
void	handle_readline_eof(char *clean_delimiter)
{
	ft_dprintf(2, "warning: delimited by EOF (wanted `%s')\n",
		clean_delimiter);
}