#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"
# include "parser.h"
# include <sys/wait.h>
# include <errno.h>

int		handle_redirection(t_cmd *command);
int		execute_pipeline(t_pipeline *pipeline, char **env);
void	execute_command(t_cmd *command, char **env);

#endif /* EXECUTION_H */