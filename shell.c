#include "shell.h"

void display_prompt(void)
{
    if (isatty(STDIN_FILENO))
    {
        printf("#cisfun$ ");
        fflush(stdout);
    }
}

ssize_t read_line(char **line, size_t *bufsize)
{
    ssize_t len = getline(line, bufsize, stdin);

    if (len == -1)
        return -1;

    if (len > 0 && (*line)[len - 1] == '\n')
        (*line)[len - 1] = '\0';

    if ((*line)[0] == '\0')
        return 0;

    return len;
}

void execute_cmd(char *line, char *program_name, char **env)
{
    static int line_number = 1;
    pid_t child_pid;
    char *argv[2];
    int status;

    child_pid = fork();
    if (child_pid == -1)
    {
        perror(program_name);
        return;
    }

    if (child_pid == 0)
    {
        argv[0] = line;
        argv[1] = NULL;

        if (execve(line, argv, env) == -1)
        {
            fprintf(stderr, "%s: %d: %s: not found\n", program_name, line_number, line);
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        wait(&status);
    }

    line_number++;
}
