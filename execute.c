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

	pid = fork();
	if (pid == 0)
	{
		if (execve(args[0], args, environ) == -1)
		{
			perror(program_name);
			free(args);
			exit(1);
		}
	}
	else if (pid < 0)
	{
		perror("Fork failed");
		return (1);
	}
	else
	{
		wait(&status);
	}
	return (0);
}
