#include "../../includes/minishell.h"

int	is_redirection(t_token_type type)
{
	return (type == REDIRECT_IN || type == REDIRECT_OUT
		|| type == APPEND || type == HEREDOC);
}

void	set_syntax_error(t_pars_context *cntx, char *message)
{
	cntx->has_syntax_error = 1;
	cntx->error_message = gc_strldup(message, ft_strlen(message));
}

void	consume_token(t_pars_context *cntx)
{
	if (cntx->current_token != NULL)
		cntx->current_token = cntx->current_token->next;
}
