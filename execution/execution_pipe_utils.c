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
		{
			if (WIFEXITED(status))
				exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				exit_status = 128 + WTERMSIG(status);
		}
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
	if (handle_redirection(pipeline->head) < 0)
	{
		g_exit_status = EXIT_FAILURE;
		return (g_exit_status);
	}
	g_exit_status = execute_builtin(pipeline->head, env);
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
