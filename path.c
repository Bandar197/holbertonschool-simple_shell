#include "shell.h"

/**
 * get_path - gets the PATH environment variable
 *
 * Return: pointer to PATH value, or NULL if not found
 */
char *get_path(void)
{
	int i;

	i = 0;
	while (environ[i] != NULL)
	{
		if (strncmp(environ[i], "PATH=", 5) == 0)
			return (environ[i] + 5);
		i++;
	}
	return (NULL);
}

/**
 * build_path - builds a full command path
 * @dir: directory path
 * @command: command name
 *
 * Return: full path, or NULL on failure
 */
char *build_path(char *dir, char *command)
{
	char *full_path;

	full_path = malloc(strlen(dir) + strlen(command) + 2);
	if (full_path == NULL)
		return (NULL);

	strcpy(full_path, dir);
	strcat(full_path, "/");
	strcat(full_path, command);

	return (full_path);
}

/**
 * find_command - finds a command in PATH
 * @command: command to find
 *
 * Return: full path of command, or NULL if not found
 */
char *find_command(char *command)
{
	char *path, *path_copy, *dir, *full_path;
	struct stat st;

	if (strchr(command, '/') != NULL)
	{
		if (stat(command, &st) == 0)
			return (strdup(command));
		return (NULL);
	}

	path = get_path();
	if (path == NULL)
		return (NULL);
	path_copy = strdup(path);
	if (path_copy == NULL)
		return (NULL);

	dir = strtok(path_copy, ":");
	while (dir != NULL)
	{
		full_path = build_path(dir, command);
		if (full_path == NULL)
			break;
		if (stat(full_path, &st) == 0)
		{
			free(path_copy);
			return (full_path);
		}
		free(full_path);
		dir = strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}
