#include "shell.h"

/**
 * run_child - Executes command in child process
 * @args: Array of command and arguments
 * @program_name: Name of executable for error display
 * @count: Command number
 * @command_path: Full path of command
 */
static void run_child(char **args, char *program_name, int count,
	char *command_path)
{
	if (execve(command_path, args, environ) == -1)
	{
		fprintf(stderr, "%s: %d: %s: %s\n",
			program_name, count, args[0], strerror(errno));
		free(command_path);
		free(args);
		_exit(126);
	}
}

/**
 * execute_cmd - Forks process and executes the command
 * @args: Array of command and arguments
 * @program_name: Name of executable for error display
 * @count: Command number
 *
 * Return: Command exit status
 */
int execute_cmd(char **args, char *program_name, int count)
{
	pid_t pid;
	int status;
	char *command_path;

	command_path = find_command(args[0]);
	if (command_path == NULL)
	{
		fprintf(stderr, "%s: %d: %s: not found\n",
			program_name, count, args[0]);
		return (127);
	}

	pid = fork();
	if (pid == 0)
		run_child(args, program_name, count, command_path);
	else if (pid < 0)
	{
		perror("Fork failed");
		free(command_path);
		return (1);
	}

	wait(&status);
	free(command_path);

	if (WIFEXITED(status))
		return (WEXITSTATUS(status));

	return (1);
}
