#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"
# include "parser.h"
# include <sys/wait.h>
# include <errno.h>

/* Execution functions */

int		handle_redirection(t_cmd *command);
int		execute_pipeline(t_pipeline *pipeline, char **env);
void	execute_command(t_cmd *command, char **env);
int		execute_builtin(t_cmd *cmd, char **env, int exit_status);

/* Environment functions */

char	**create_env(char **env);
char	*get_env(char **env, const char *name);
char	**get_path_env(char **env);
char	*find_executable_path(char *cmd, char **env);
void    set_custom_var(char *key, char *value, char **env);

/* Built-in command functions */

int     env_builtin(char **env);
int     export_builtin(char **args, char **env);
int     unset_builtin(char **args, char **env);
int     pwd_builtin(char **env);


/* Built-in helper functions */

int		is_builtin(const char *cmd);

#endif /* EXECUTION_H */