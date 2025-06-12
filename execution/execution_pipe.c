#include "../includes/execution.h"

/**
 * open_pipe_if_needed - Opens a pipe if the command has a next command.
 * @cmd: The current command.
 * @pipe_fd: The file descriptors for the pipe.
 * Returns: 0 on success, -1 on failure.
 */
static int	open_pipe_if_needed(t_cmd *cmd, int *pipe_fd)
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
static pid_t	fork_and_setup(t_cmd *cmd, int *pipe_fd,
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
static void	close_fds(int *prev_fd, int *pipe_fd, t_cmd *cmd)
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
 * wait_for_children - Waits for all child processes to finish.
 * @pids: Array of PIDs of the child processes.
 * @cmd_count: The number of commands in the pipeline.
 */
static void	wait_for_children(pid_t *pids, int cmd_count)
{
	int	i;

	i = 0;
	while (i < cmd_count)
	{
		waitpid(pids[i], NULL, 0);
		i++;
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
	t_cmd	*current_cmd;
	int		pipe_fd[2];
	int		prev_fd;
	int		cmd_count;
	pid_t	*pids;

	if (pipeline == NULL || pipeline->head == NULL)
		return (EXIT_FAILURE);
	/* Builtin redirection is bugged at the moment, need to restore original FDs after execution */
	if (pipeline->cmd_count == 1 && is_builtin(pipeline->head->args[0]) == 1)
	{
    	if (handle_redirection(pipeline->head) < 0)
            return (EXIT_FAILURE);
		return (execute_builtin(pipeline->head, env, 0));
	}
	pids = gc_alloc(sizeof(pid_t) * 256);
	if (pids == NULL)
		return (EXIT_FAILURE);
	current_cmd = pipeline->head;
	prev_fd = -1;
	cmd_count = 0;
	while (current_cmd != NULL)
	{
		if (open_pipe_if_needed(current_cmd, pipe_fd) < 0)
			return (EXIT_FAILURE);
		pids[cmd_count++] = fork_and_setup(current_cmd, pipe_fd, prev_fd, env);
		close_fds(&prev_fd, pipe_fd, current_cmd);
		current_cmd = current_cmd->next;
	}
	wait_for_children(pids, cmd_count);
	return (EXIT_SUCCESS);
}
