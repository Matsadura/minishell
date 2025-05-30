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
# include "garbage_collector/gc_header.h"

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

void	echo(char **args);
int		change_dir(t_env **env_list, const char *path);
void	pwd(t_env *env);
void	export_var(t_env **env_list, char *key, char *value);
void	unset_var(t_env **env_list, char *key);
void	print_env(t_env *env_list);
int		exit_builtin(char **args);

/* Environment */

t_env	*create_env(char **env);
t_env	*add_var(char *var);
void	add_var_back(t_env **lst, t_env *var);
void	del_var(t_env **lst, char *var);
char	*get_env(t_env *env_list, const char *var);

#endif
