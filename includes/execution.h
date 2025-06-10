#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"
# include "parser.h"
# include <sys/wait.h>

int			execute_command(t_cmd *command, char **env);
int			execute_pipeline(t_pipeline *pipeline, char **env);

#endif /* EXECUTION_H */