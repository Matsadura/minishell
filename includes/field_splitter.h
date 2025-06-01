#ifndef FIELD_SPLITTER_H
# define FIELD_SPLITTER_H

# include "minishell.h"

typedef struct s_field_context
{
	int		was_quoted;
	int		needs_splitting;
}	t_field_context;


char	**ft_split_by_space(char const	*s);

#endif