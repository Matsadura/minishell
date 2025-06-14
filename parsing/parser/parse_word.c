/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberkass <aberkass@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 21:25:52 by aberkass          #+#    #+#             */
/*   Updated: 2025/05/06 03:15:30 by aberkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * parse_word - parses a WORD token and adds it to the command arguments array
 * @cntxt: parser context containing the current token
 * @args: pointer to the arguments array to be expanded
 * @arg_count: pointer to the current argument count
 * return: 1 on success, 0 on failure
 */
int	parse_word(t_pars_context *cntxt, char ***args, int *arg_count)
{
	char	**new_args;
	int		i;

	if (cntxt->current_token == NULL
		|| cntxt->current_token->value == NULL)
		return (0);
	new_args = gc_alloc(sizeof(char *) * (*arg_count + 2));
	if (new_args == NULL)
		return (0);
	i = 0;
	while (i < *arg_count)
	{
		new_args[i] = (*args)[i];
		i++;
	}
	new_args[*arg_count] = gc_strldup(cntxt->current_token->value,
			ft_strlen(cntxt->current_token->value));
	new_args[*arg_count + 1] = NULL;
	*args = new_args;
	(*arg_count)++;
	consume_token(cntxt);
	return (1);
}
