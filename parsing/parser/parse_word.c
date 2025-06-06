#include "../../includes/minishell.h"

int	parse_word(t_pars_context *cntx, char ***args, int *arg_count)
{
	char	**new_args;
	int		i;

	if (cntx->current_token == NULL
		|| cntx->current_token->value == NULL)
		return (0);
	new_args = gc_alloc(sizeof(char *) * (*arg_count + 2));
	if (new_args == NULL)
		return (0);
	i = 0;
	while (i < *arg_count)
	{
		new_args[i] = (*args)[i];
		i++;
	}
	new_args[*arg_count] = gc_strldup(cntx->current_token->value,
			ft_strlen(cntx->current_token->value));
	new_args[*arg_count + 1] = NULL;
	*args = new_args;
	(*arg_count)++;
	consume_token(cntx);
	return (1);
}
