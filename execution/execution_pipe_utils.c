/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_pipe_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaoui <zzaoui@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 17:13:48 by zzaoui            #+#    #+#             */
/*   Updated: 2025/06/13 17:13:53 by zzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

/**
 * get_exit_status - Retrieves the exit status of a child process.
 * @status: The status returned by waitpid.
 * Returns: The exit status of the child process.
 */
static int	get_exit_status(int status)
{
	int	sig;

	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGINT)
			return (130);
		else if (sig == SIGQUIT)
			return (131);
		else
			return (128 + sig);
	}
	return (0);
}

/**
 * wait_for_children - Waits for all child processes to finish.
 * @pids: Array of PIDs of the child processes.
 * @cmd_count: The number of commands in the pipeline.
 */
int	wait_for_children(pid_t *pids, int cmd_count)
{
	int	i;
	int	status;
	int	exit_status;

	i = 0;
	exit_status = 0;
	while (i < cmd_count)
	{
		waitpid(pids[i], &status, 0);
		if (i == cmd_count - 1)
			exit_status = get_exit_status(status);
		i++;
	}
	return (exit_status);
}

/**
 * handle_single_builtin - Handles the execution of a single built-in command
 * @pipeline: The pipeline containing the single command.
 * @env: The environment variables to pass to the command.
 * Returns: The exit status of the built-in command.
 */
int	handle_single_builtin(t_pipeline *pipeline, char **env)
{
	int	saved_stdin;
	int	saved_stdout;
	int	result;

	saved_stdin = -1;
	saved_stdout = -1;
	if (pipeline->head->redirections != NULL)
	{
		if (save_and_redirect_builtin(pipeline->head,
				&saved_stdin, &saved_stdout) < 0)
		{
			g_exit_status = EXIT_FAILURE;
			return (g_exit_status);
		}
	}
	result = execute_builtin(pipeline->head, env);
	if (pipeline->head->redirections != NULL)
		restore_builtin_fds(saved_stdin, saved_stdout);
	g_exit_status = result;
	return (g_exit_status);
}

/**
 * execute_pipeline_loop - Executes the commands in the pipeline.
 * @pipeline: The pipeline containing the commands to execute.
 * @env: The environment variables to pass to the commands.
 * @pids: Array to store the PIDs of the child processes.
 * Returns: The number of commands executed, or -1 on failure.
 */
int	execute_pipeline_loop(t_pipeline *pipeline, char **env, pid_t *pids)
{
	t_cmd	*current_cmd;
	int		pipe_fd[2];
	int		prev_fd;
	int		cmd_count;

	current_cmd = pipeline->head;
	prev_fd = -1;
	cmd_count = 0;
	while (current_cmd != NULL)
	{
		if (open_pipe_if_needed(current_cmd, pipe_fd) < 0)
		{
			g_exit_status = EXIT_FAILURE;
			return (-1);
		}
		pids[cmd_count++] = fork_and_setup(current_cmd, pipe_fd, prev_fd, env);
		close_fds(&prev_fd, pipe_fd, current_cmd);
		current_cmd = current_cmd->next;
	}
	return (cmd_count);
}
