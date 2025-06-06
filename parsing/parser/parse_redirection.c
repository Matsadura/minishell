#include "../../includes/minishell.h"

static t_redirect	*create_redirect_node(t_pars_context *cntx
	, t_token_type type)
{
	t_redirect	*redirect;

	redirect = gc_alloc(sizeof(t_redirect));
	if (redirect == NULL)
		return (NULL);
	redirect->type = type;
	redirect->filename = gc_strldup(cntx->current_token->value,
			ft_strlen(cntx->current_token->value));
	redirect->next = NULL;
	return (redirect);
}

static void	append_to_redirections(t_redirect *redirect
	, t_redirect **redirections)
{
	t_redirect	*current;

	if (*redirections == NULL)
	{
		*redirections = redirect;
		return ;
	}
	current = *redirections;
	while (current->next != NULL)
		current = current->next;
	current->next = redirect;
	return ;
}

int	parse_redirect(t_pars_context *cntx, t_redirect **redirections)
{
	t_redirect		*redirect_node;
	t_token_type	redirect_type;

	if (cntx->current_token == NULL
		|| (cntx->current_token->type) == 0)
		return (0);
	redirect_type = cntx->current_token->type;
	consume_token(cntx);
	if (cntx->current_token == NULL || cntx->current_token->type != WORD)
	{
		set_syntax_error(cntx, "syntax error near unexpected token");
		return (0);
	}
	redirect_node = create_redirect_node(cntx, redirect_type);
	if (redirect_node == NULL)
		return (0);
	append_to_redirections(redirect_node, redirections);
	consume_token(cntx);
	return (1);
}
