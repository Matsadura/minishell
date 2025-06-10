#include "../includes/execution.h"

int execute_command(t_cmd *command, char **env)
{
	pid_t		pid;
	t_redirect	*redir;

	if (command == NULL || command->args == NULL || command->args[0] == NULL)
		return (-1);
	redir = command->redirections;
	while (redir != NULL)
	{
		if (redir->type == REDIRECT_IN)
			command->input_fd = open(redir->filename, O_RDONLY);
		else if (redir->type == REDIRECT_OUT)
			command->output_fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		redir = redir->next;
	}
	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid == 0)
	{
		if (command->input_fd != -1)
			dup2(command->input_fd, STDIN_FILENO);
		if (command->output_fd != -1)
			dup2(command->output_fd, STDOUT_FILENO);

		printf("Executing command: %s\n", command->args[0]);
		execve(command->args[0], command->args, env);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	waitpid(pid, &command->pid, 0);
	return (WEXITSTATUS(command->pid));
}

int execute_pipeline(t_pipeline *pipeline, char **env)
{
	t_cmd	*current_cmd;
	int		exit_status;

	if (pipeline == NULL || pipeline->head == NULL)
		return (EXIT_FAILURE);
	current_cmd = pipeline->head;
	exit_status = 0;
	while (current_cmd != NULL)
	{
		exit_status = execute_command(current_cmd, env);
		if (exit_status != 0)
			break;
		current_cmd = current_cmd->next;
	}
	return (exit_status);
}
