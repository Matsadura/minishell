#ifndef FIELD_SPLITTER_H
# define FIELD_SPLITTER_H

# include "minishell.h"

typedef struct s_field_context
{
	int		was_quoted;
	int		needs_splitting;
}	t_field_context;

//fields splitter
t_token	*field_splitter(t_token *tokens);

//fields splitter utils
int		contains_whitespace(char *str);
int		should_split_token(t_token *token, t_field_context *cntxt);
t_token	*create_field_list(char **fields, t_token *original);
t_token	*split_token(t_token *token, t_field_context *cntxt);
void	append_token_list(t_token **dest, t_token *src);
char	**ft_split_by_space(char const	*s);
void	free_fields_array(char **fields);

#endif