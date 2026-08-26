#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

extern char **environ;

void run_shell(char *program_name);
int execute_cmd(char **args, char *program_name, int count);char **tokenize_line(char *line);
char *get_path(void);
char *find_command(char *command);
char *build_path(char *dir, char *command);


#endif /* SHELL_H */
