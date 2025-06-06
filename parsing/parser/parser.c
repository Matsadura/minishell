#include "../../includes/minishell.h"

static void	init_parser_context(t_pars_context *cntx, t_token *tokens)
{
	cntx->token_list = tokens;
	cntx->current_token = tokens;
	cntx->has_syntax_error = 0;
	cntx->error_message = NULL;
}

t_cmd	*parse_tokens(t_token *tokens)
{
	t_cmd			*command_list;
	t_pars_context	cntx;

	init_parser_context(&cntx, tokens);
	command_list = pipeline(&cntx);
	if (cntx.has_syntax_error == 1)
	{
		if (cntx.error_message != NULL)
		{
			ft_dprintf(2, "minishell: %s\n", cntx.error_message);
			gc_free(cntx.error_message);
		}
		return (NULL);
	}
	return (command_list);
}
