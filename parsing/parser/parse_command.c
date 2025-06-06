#include "../../includes/minishell.h"

static t_cmd	*init_cmd_node(void)
{
	t_cmd	*cmd;

	cmd = gc_alloc(sizeof(t_cmd));
	if (cmd == NULL)
		return (NULL);
	cmd->args = NULL;
	cmd->redirections = NULL;
	cmd->next = NULL;
	return (cmd);
}

static int	is_cmd_token(t_pars_context *cntx)
{
	return (is_redirection(cntx->current_token->type)
		|| cntx->current_token->type == WORD);
}

static int	process_cmd_token(t_pars_context *cntx, t_cmd *cmd, int *count)
{
	if (is_redirection(cntx->current_token->type))
	{
		if (parse_redirect(cntx, &cmd->redirections) == 0)
			return (0);
	}
	else if (cntx->current_token->type == WORD)
	{
		if (parse_word(cntx, &cmd->args, count) == 0)
			return (0);
	}
	return (1);
}

static int	has_cmd_content(t_cmd *cmd, int args_count)
{
	return (cmd->redirections != NULL || args_count > 0);
}

t_cmd	*command(t_pars_context *cntx)
{
	t_cmd	*cmd_node;
	int		args_count;

	args_count = 0;
	cmd_node = init_cmd_node();
	if (cmd_node == NULL)
		return (NULL);
	while (cntx->current_token != NULL && is_cmd_token(cntx))
	{
		if (process_cmd_token(cntx, cmd_node, &args_count) == 0)
			return (NULL);
	}
	if (has_cmd_content(cmd_node, args_count) == 0)
	{
		set_syntax_error(cntx, "syntax error empty command");
		return (NULL);
	}
	return (cmd_node);
}
