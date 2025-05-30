#include "libft.h"

/**
 * ft_isnumber - Checks if arg is a number
 * @arg: The element to check
 * Return: 1 if true, 0 otherwise
 */
int	ft_isnumber(char *arg)
{
	int	i;

	if (arg == NULL || *arg == '\0')
		return (0);
	i = 0;
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	while (arg[i])
	{
		if (ft_isdigit(arg[i]) != 1)
			return (0);
		i++;
	}
	return (1);
}
