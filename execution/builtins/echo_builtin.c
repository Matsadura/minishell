#include "../../includes/execution.h"

/**
 * echo_builtin - Prints the arguments passed to the echo command.
 * @args: The arguments passed to the echo command.
 * Returns: 0 on success, 1 on failure.
 */
int	echo_builtin(char **args)
{
	int	i;
	int	newline;

	if (args == NULL || args[0] == NULL)
		return (1);
	newline = 1;
	i = 1;
	if (args[i] && ft_strcmp(args[i], "-n") == 0)
	{
		newline = 0;
		i++;
	}
	while (args[i])
	{
		ft_printf("%s", args[i]);
		if (args[i + 1])
			ft_printf(" ");
		i++;
	}
	if (newline)
		ft_printf("\n");
	return (0);
}
