/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberkass <aberkass@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 21:26:06 by aberkass          #+#    #+#             */
/*   Updated: 2025/05/01 21:26:13 by aberkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* Libraries */
# include "../libft/libft.h"
# include "../garbage_collector/gc_header.h"
# include "lexer.h"
# include "tokeniser.h"
# include "expander.h"
# include "fields_splitter.h"
# include "parser.h"
# include "execution.h"
# include <readline/readline.h>
# include <readline/history.h>

/* Macros */
# define TRUE 1
# define FALSE 0

# define STDIN 0
# define STDOUT 1
# define STDERR 2

#endif
