/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberkass <aberkass@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 21:25:52 by aberkass          #+#    #+#             */
/*   Updated: 2025/05/06 03:15:30 by aberkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * create_redirect_node - creates a new redirection node with specified type
 * @cntxt: parser context containing the filename token
 * @type: type of redirection (REDIRECT_IN, REDIRECT_OUT, APPEND, HEREDOC)
 * return: pointer to new redirection node or NULL on allocation failure
 */
static t_redirect	*create_redirect_node(t_pars_context *cntxt
	, t_token_type type)
{
	t_redirect	*redirect;

	redirect = gc_alloc(sizeof(t_redirect));
	if (redirect == NULL)
		return (NULL);
	redirect->type = type;
	redirect->filename = gc_strldup(cntxt->current_token->value,
			ft_strlen(cntxt->current_token->value));
	redirect->fd = -1;
	redirect->temp_file = NULL;
	redirect->next = NULL;
	return (redirect);
}

/**
 * append_to_redirections - appends a redirection node to the end of the list
 * @redirect: redirection node to append
 * @redirections: pointer to the head of the redirections list
 */
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

/**
 * parse_redirect - parses a redirection operator and its target filename
 * @cntxt: parser context containing the redirection tokens
 * @redirections: pointer to the redirections list to append to
 * return: 1 on success, 0 on syntax error
 */
int	parse_redirect(t_pars_context *cntxt, t_redirect **redirections)
{
	t_redirect		*redirect_node;
	t_token_type	redirect_type;

	if (cntxt->current_token == NULL
		|| (cntxt->current_token->type) == 0)
		return (0);
	redirect_type = cntxt->current_token->type;
	consume_token(cntxt);
	if (cntxt->current_token == NULL || cntxt->current_token->type != WORD)
	{
		set_syntax_error(cntxt, "syntax error near unexpected token");
		return (0);
	}
	redirect_node = create_redirect_node(cntxt, redirect_type);
	if (redirect_node == NULL)
		return (0);
	append_to_redirections(redirect_node, redirections);
	consume_token(cntxt);
	return (1);
}
