#include "shell.h"

/**
 * execute_cmd - Forks process and executes the command
 * @args: Array of command and arguments
 * @program_name: Name of executable for error display
 *
 * Return: 0 on success, 1 on failure
 */
int execute_cmd(char **args, char *program_name)
{
	pid_t pid;
	int status;
	char *command_path;

	command_path = find_command(args[0]);

	if (command_path == NULL)
	{
		fprintf(stderr, "%s: %s: not found\n",
			program_name, args[0]);
		return (1);
	}

	pid = fork();

	if (pid == 0)
	{
		if (execve(command_path, args, environ) == -1)
		{
			perror(program_name);
			free(command_path);
			free(args);
			exit(1);
		}
	}
	else if (pid < 0)
	{
		perror("Fork failed");
		free(command_path);
		return (1);
	}
	else
	{
		wait(&status);
	}

	free(command_path);
	return (0);
}
