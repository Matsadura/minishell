#include "libft.h"

/**
 * ft_strarrlen - Calculates the length of a NULL-terminated array of strings.
 * @arr: The array of strings to measure.
 * Returns: The number of strings in the array, excluding the NULL terminator.
 */
int	ft_strarrlen(char **arr)
{
	int	i;

	if (arr == NULL)
		return (0);
	i = 0;
	while (arr[i] != NULL)
		i++;
	return (i);
}