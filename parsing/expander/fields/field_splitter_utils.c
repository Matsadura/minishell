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

t_token	*create_field_list(char **fields, t_token *original)
{
	int		i;
	t_token	*list;
	t_token	*node;

	if (fields == NULL)
		return (NULL);
	list = NULL;
	i = 0;
	while (fields[i] != NULL)
	{
		node = create_token_node(fields[i], WORD);
		if (node == NULL)
			return (list);
		add_token(&list, node);
		i++;
	}
	return (list);
}

t_token	*split_token(t_token *token, t_field_context *cntxt)
{
	char	**fields;
	t_token	*field_list;

	if (cntxt->needs_splitting == 0)
		return (create_token_node(token->value, token->type));
	fields = ft_split_by_space(token->value);
	if (fields == NULL || fields[0] == NULL)
	{
		/*printf("need to free?\n");*/
		return (create_token_node(token->value, token->type));
	}
	field_list = create_field_list(fields, token);
	return (field_list);
}

void	append_token_list(t_token **dest, t_token *src)
{
	t_token	*current;

	if (src == NULL)
		return (NULL);
	if (*dest == NULL)
	{
		*dest = src;
		return ;
	}
	current = *dest;
	while (current->next != NULL)
		current = current->next;
	current->next = src;
}