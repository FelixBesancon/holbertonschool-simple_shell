#ifndef SHELL_H
#define SHELL_H

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

ssize_t read_line(char **line, size_t *bufsize);
void display_prompt(void);
void execute_cmd(char *line, char *program_name, char **env);

#endif
