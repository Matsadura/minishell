#include "../../../includes/minishell.h"

t_token	*field_splitter(t_token *tokens)
{
	t_token			*current;
	t_token			*split_tokens;
	t_token			*new_list;
	t_field_context	cntxt;

	new_list = NULL;
	current = tokens;
	while (current != NULL)
	{
		if (should_split_token(current, &cntxt))
		{
			split_tokens = split_token(current, &cntxt);
			append_token_list(&new_list, split_token);
		}
		else
			add_token(&new_list, create_token_node(current->value, current->type));
		current = current->next;
	}
	return (new_list);
}