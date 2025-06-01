#include "../../../includes/minishell.h"

t_token	*field_splitter(t_token *tokens)
{
	t_token			*current;
	t_token			*split_tokens;
	t_token			*new_node;
	t_token			*new_list;
	t_field_context	cntxt;

	new_list = NULL;
	current = tokens;
	ft_memset(&cntxt, 0, sizeof(cntxt));
	while (current != NULL)
	{
		if (should_split_token(current, &cntxt))
		{
			split_tokens = split_token(current, &cntxt);
			if (split_tokens != NULL)
				append_token_list(&new_list, split_tokens);
		}
		else
		{
			new_node = create_token_node(current->value, current->type);
			if (new_node != NULL)
				add_token(&new_list, new_node);
		}
		current = current->next;
	}
	return (new_list);
}