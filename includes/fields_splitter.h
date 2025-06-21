/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fields_splitter.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberkass <aberkass@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 12:00:16 by aberkass          #+#    #+#             */
/*   Updated: 2025/06/01 22:39:05 by aberkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIELDS_SPLITTER_H
# define FIELDS_SPLITTER_H

# include "minishell.h"

typedef struct s_field_context
{
	int				was_quoted;
	int				needs_splitting;
	int				is_redirect_target;
	t_token_type	prev_token_type;
}	t_field_context;

//fields splitter
t_token	*field_splitter(t_token *tokens, char **env);

//fields splitter utils
int		contains_whitespace(char *str);
int		should_split_token_ifs(t_token *token, t_token *prev_token,
		 t_field_context *cntxt, char **env);
t_token	*split_token(t_token *token, t_field_context *cntxt, char **env);
void	append_token_list(t_token **dest, t_token *src);
void	free_fields_array(char **fields);

//ifs utils
char	**split_by_ifs(char const *s, char *ifs);
char	*get_ifs_value(char **env);
int		is_ifs_char(char c, char *ifs);
int		contains_ifs_character(char *str, char *ifs);

//ambiguous redirect handlers
void	set_redirect_context(t_token *token, t_token *prev_token,
			t_field_context *cntxt);
int		is_ambiguous_redirect(char **fields, t_field_context *cntxt);

#endif