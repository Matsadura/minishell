#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

typedef struct s_redirect
{
	t_token_type		type;
	char				*filename;
	struct s_redirect	*next;
}	t_redirect;

typedef struct s_cmd
{
	char			**args;
	t_redirect		*redirections;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_pars_context
{
	t_token	*token_list;
	t_token	*current_token;
	int		has_syntax_error;
	char	*error_message;
}	t_pars_context;

//main parser function
t_cmd	*parse_tokens(t_token *tokens);

t_cmd	*pipeline(t_pars_context *cntx);
t_cmd	*command(t_pars_context *cntx);

int		is_redirection(t_token_type type);
void	set_syntax_error(t_pars_context *cntx, char *message);
void	consume_token(t_pars_context *cntx);

int	parse_word(t_pars_context *cntx, char ***args, int *arg_count);
int	parse_redirect(t_pars_context *cntx, t_redirect **redirections);

#endif