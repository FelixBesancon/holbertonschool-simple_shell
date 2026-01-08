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
void execute_cmd(char **line, char *prog_name, char **env, int *last_status);
int tokenize_line(char *line, char **argv, int max_args);
void run_command(char **argv, char *prog_name, char **env, int *line_nb, int *last_status);
int execute_builtin(char **argv, char **env, char **line, int *last_status);
char *get_full_path(char *cmd, char **env);
char *find_in_path(char *path_env, char *cmd);

#endif
