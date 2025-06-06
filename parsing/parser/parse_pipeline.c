#include "../../includes/minishell.h"

static int	handle_pipe(t_pars_context *cntx)
{
	consume_token(cntx);
	if (cntx->current_token == NULL)
	{
		set_syntax_error(cntx, "syntax error expected command after pipe");
		return (0);
	}
	return (1);
}

static void	link_commands(t_cmd **current, t_cmd *cmd)
{
	(*current)->next = cmd;
	*current = cmd;
}

t_cmd	*pipeline(t_pars_context *cntx)
{
	t_cmd	*head;
	t_cmd	*new_cmd;
	t_cmd	*current;

	head = command(cntx);
	if (head == NULL)
		return (NULL);
	current = head;
	while (cntx->current_token && cntx->current_token->type == PIPE)
	{
		if (handle_pipe(cntx) == 0)
			return (NULL);
		new_cmd = command(cntx);
		if (new_cmd == NULL)
			return (NULL);
		link_commands(&current, new_cmd);
	}
	if (cntx->current_token != NULL)
	{
		set_syntax_error(cntx, "syntax error unexpect token");
		return (NULL);
	}
	return (head);
}
