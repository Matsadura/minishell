/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaoui <zzaoui@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 17:15:49 by zzaoui            #+#    #+#             */
/*   Updated: 2025/06/13 17:15:50 by zzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"
# include "parser.h"
# include <sys/wait.h>
# include <errno.h>
# include <signal.h>

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

/* Redirection helper functions */

int		handle_single_redir(t_cmd *command, t_redirect *redir);
int		handle_redir_in(t_cmd *command, t_redirect *redir);
int		handle_redir_out(t_cmd *command, t_redirect *redir);
int		handle_redir_append(t_cmd *command, t_redirect *redir);
int		handle_redir_heredoc(t_cmd *command, t_redirect *redir);
char	*create_temp_file(void);
int		write_heredoc_content(char *temp_file, char *delimiter);
int		preprocess_heredocs(t_pipeline *pipeline);
int		redir_heredoc(t_cmd *command, t_redirect *redir);

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
int		save_and_redirect_builtin(t_cmd *command, int *saved_stdin,
			int *saved_stdout);
void	restore_builtin_fds(int saved_stdin, int saved_stdout);

/* Signals functions */

void	sigint_handler(int sig);
void	sigquit_handler(int sig);
void	sigint_child_handler(int sig);
void	sigquit_child_handler(int sig);
void	setup_signals(void);
void	setup_child_signals(void);
void	ignore_signals(void);
void	restore_signals(void);

#endif /* EXECUTION_H */
