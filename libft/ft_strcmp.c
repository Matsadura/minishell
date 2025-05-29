#include "libft.h"

/**
 * ft_strcmp - Compares two strings
 * @s1: First string
 * @s2: Second string
 * Return: An integer less than, equal to, or greater than
 * zero if s1 is found, respectively, to be less than,
 * equal to, or greater than s2
 */
int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
