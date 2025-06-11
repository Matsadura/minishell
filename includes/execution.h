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

/* Environment functions */

char	**create_env(char **env);
char	*get_env(char **env, const char *name);
char	**get_path_env(char **env);
char	*find_executable_path(char *cmd, char **env);

#endif /* EXECUTION_H */