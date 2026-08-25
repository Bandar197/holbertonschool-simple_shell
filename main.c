#include "shell.h"

/**
 * main - Entry point for simple shell
 * @ac: Argument count (unused)
 * @av: Argument vector
 *
 * Return: Always 0
 */
int main(int ac, char **av)
{
	(void)ac;
	run_shell(av[0]);
	return (0);
}
