/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaoui <zzaoui@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 21:26:06 by aberkass          #+#    #+#             */
/*   Updated: 2025/05/22 14:43:09 by zzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* Libraries */

# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

/* Macros */

# define TRUE 1
# define FALSE 0

# define STDIN 0
# define STDOUT 1
# define STDERR 2

/* Structures */

typedef struct s_env
{
	char			*var;
	struct s_env	*next;
}	t_env;

/* Builtins */

void	print_env(t_env *env_list);
void	pwd(t_env *env);

/* Env helpers */

t_env	*create_env(char **env);

#endif
