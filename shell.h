#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>

extern char **environ;

void run_shell(char *program_name);
char **tokenize_line(char *line);
int execute_cmd(char **args, char *program_name, int count);
int handle_builtin(char **args, char *line, int *status);
void print_env(void);
char *get_path(void);
char *build_path(char *dir, char *command);
char *find_command(char *command);

#endif /* SHELL_H */
