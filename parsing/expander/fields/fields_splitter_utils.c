#include "../../../includes/minishell.h"

int	contains_whitespace(char *str)
{
	int	i;

	if (str == NULL)
		return (0);
	i = 0;
	while (str[i] != '\0')
	{
		if (is_white_space(str[i]))
			return (1);
		i++;
	}
	return (0);
}

int	should_split_token(t_token *token, t_field_context *cntxt)
{
	if (token->type == D_QUOTE || token->type == S_QUOTE)
		cntxt->was_quoted = 1;
	cntxt->needs_splitting = 0;
	if (token->type == WORD && cntxt->was_quoted == 0)
	{
		if (contains_whitespace(token->value))
			cntxt->needs_splitting = 1;
	}
	return (cntxt->needs_splitting);
}

void	free_fields_array(char **fields)
{
	int	i;

	if (fields == NULL)
		return ;
	i = 0;
	while (fields[i] != NULL)
	{
		gc_free(fields[i]);
		i++;
	}
	gc_free(fields);
}