/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberkass <aberkass@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:57:11 by aberkass          #+#    #+#             */
/*   Updated: 2025/05/27 16:58:13 by aberkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "minishell.h"

typedef enum e_exp_state
{
	NORMAL,
	DOUBLE_QUOTES,
	SINGLE_QUOTES
}	t_exp_state;

typedef struct s_exp_context
{
	char			**env;
	int				last_exit_status;
	t_exp_state		state;
	int				quote_removal;
	int				needs_splitting;
}	t_exp_context;

//main expander function
t_token	*expander(t_token *tokens, char **env, int exit_status);

//expander utils
char	*expand_token(char *token, t_exp_context *cntx);
int		process_char(char *token, char **res, int i, t_exp_context *cntx);
int		handle_single_quotes(int i, t_exp_context *cntx);
int		handle_double_quotes(int i, t_exp_context *cntx);
char	*append_char_to_str(const char *str, char c);
char	*append_str_to_str(char *dst, const char *src);
int		handle_regular_character(char *token, char **res, int i);

//quotes processing
char	*process_quoted_token(char *val, t_token_type type, t_exp_context *ctx);
char	*remove_outer_quotes(char *token_str, char quote_char);

//variable expansion
int		handle_var_expansion(char *val, char **res, int i, t_exp_context *cntx);
char	*extract_variable_name(char *token, int *indx);
char	*get_var_value(char *var_name, t_exp_context *cntx);

#endif