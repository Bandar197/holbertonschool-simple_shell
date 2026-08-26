#include "shell.h"

/**
 * run_shell - Main loop to process user commands
 * @program_name: Name of the executable (argv[0])
 */
void run_shell(char *program_name)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read_bytes;
	char **args;
	int count;
	int status;

	count = 0;
	status = 0;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "#cisfun$ ", 9);

		read_bytes = getline(&line, &len, stdin);
		if (read_bytes == -1)
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			free(line);
			exit(status);
		}

		count++;

		if (line[read_bytes - 1] == '\n')
			line[read_bytes - 1] = '\0';

		args = tokenize_line(line);
		if (args && args[0])
			status = execute_cmd(args, program_name, count);

		free(args);
	}
}

/**
 * tokenize_line - Splits input line into command and arguments
 * @line: Raw string input
 *
 * Return: Array of argument strings
 */
char **tokenize_line(char *line)
{
	char **tokens;
	char *token;
	int i;

	i = 0;
	tokens = malloc(sizeof(char *) * 64);
	if (tokens == NULL)
		return (NULL);

	token = strtok(line, " \t\r\n\a");
	while (token != NULL)
	{
		tokens[i] = token;
		i++;
		token = strtok(NULL, " \t\r\n\a");
	}

	tokens[i] = NULL;
	return (tokens);
}
