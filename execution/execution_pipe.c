#include "../includes/execution.h"

/**
 * open_pipe_if_needed - Opens a pipe if the command has a next command.
 * @cmd: The current command.
 * @pipe_fd: The file descriptors for the pipe.
 * Returns: 0 on success, -1 on failure.
 */
int	open_pipe_if_needed(t_cmd *cmd, int *pipe_fd)
{
	if (cmd->next && pipe(pipe_fd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	return (0);
}

/**
 * fork_and_setup - Forks a new process
 * 		and sets up the input/output redirections.
 * @cmd: The command to execute in the child process.
 * @pipe_fd: The file descriptors for the pipe.
 * @prev_fd: The file descriptor for the previous command's output.
 * @env: The environment variables to pass to the command.
 * Returns: The PID of the child process on success, -1 on failure.
 */
pid_t	fork_and_setup(t_cmd *cmd, int *pipe_fd,
	int prev_fd, char **env)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (-1);
	}
	if (pid == 0)
	{
		if (prev_fd != -1)
		{
			dup2(prev_fd, STDIN);
			close(prev_fd);
		}
		if (cmd->next != NULL)
		{
			dup2(pipe_fd[1], STDOUT);
			close(pipe_fd[0]);
			close(pipe_fd[1]);
		}
		execute_command(cmd, env);
		exit(EXIT_FAILURE);
	}
	return (pid);
}

/**
 * close_fds - Closes the file descriptors used for the previous command
 * and the pipe if there is a next command.
 * @prev_fd: Pointer to the previous command's output file descriptor.
 * @pipe_fd: The file descriptors for the pipe.
 * @cmd: The current command.
 */
void	close_fds(int *prev_fd, int *pipe_fd, t_cmd *cmd)
{
	if (*prev_fd != -1)
		close(*prev_fd);
	if (cmd->next != NULL)
	{
		close(pipe_fd[1]);
		*prev_fd = pipe_fd[0];
	}
}

/**
 * execute_pipeline - Executes a pipeline of commands.
 * @pipeline: The pipeline containing the commands to execute.
 * @env: The environment variables to pass to the commands.
 * Returns: EXIT_STATUS.
 */
int	execute_pipeline(t_pipeline *pipeline, char **env)
{
	pid_t	*pids;
	int		cmd_count;

	if (pipeline == NULL || pipeline->head == NULL)
		return (EXIT_FAILURE);
	if (pipeline->cmd_count == 1 && is_builtin(pipeline->head->args[0]) == 1)
		return (handle_single_builtin(pipeline, env));
	pids = gc_alloc(sizeof(pid_t) * 256);
	if (pids == NULL)
	{
		g_exit_status = EXIT_FAILURE;
		return (g_exit_status);
	}
	cmd_count = execute_pipeline_loop(pipeline, env, pids);
	if (cmd_count < 0)
		return (g_exit_status);
	g_exit_status = wait_for_children(pids, cmd_count);
	return (g_exit_status);
}
