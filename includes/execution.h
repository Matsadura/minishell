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
int		execute_builtin(t_cmd *cmd, char **env);

/* Execution helper functions */
int		wait_for_children(pid_t *pids, int cmd_count);
int		handle_single_builtin(t_pipeline *pipeline, char **env);
int		execute_pipeline_loop(t_pipeline *pipeline, char **env, pid_t *pids);
int		open_pipe_if_needed(t_cmd *cmd, int *pipe_fd);
pid_t	fork_and_setup(t_cmd *cmd, int *pipe_fd, int prev_fd, char **env);
void	close_fds(int *prev_fd, int *pipe_fd, t_cmd *cmd);

/* Environment functions */

char	**create_env(char **env);
char	*get_env(char **env, const char *name);
char	**get_path_env(char **env);
char	*find_executable_path(char *cmd, char **env);
void	set_custom_var(char *key, char *value, char **env);

/* Built-in command functions */

int		env_builtin(char **env);
int		export_builtin(char **args, char **env);
int		unset_builtin(char **args, char **env);
int		pwd_builtin(char **env);
int		echo_builtin(char **args);
int		cd_builtin(char **args, char **env);
int		exit_builtin(char **args);

/* Built-in helper functions */

int		is_builtin(const char *cmd);

#endif /* EXECUTION_H */