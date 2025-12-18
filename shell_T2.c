#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char **environ;

int main(void)
{
    char *line;
    size_t len;
    ssize_t nread;
    pid_t child_pid;
    int status;

    line = NULL;
    len = 0;

    while (1)
    {
        printf("#cisfun$ ");
        fflush(stdout);

        nread = getline(&line, &len, stdin);
        if (nread == -1)
        {
            printf("\n");
            break;
        }

        if (nread <= 1)
            continue;

        if (line[nread - 1] == '\n')
            line[nread - 1] = '\0';

        if (line[0] == '\0')
            continue;

        if (access(line, X_OK) == -1)
        {
            perror(line);
            continue;
        }

        child_pid = fork();
        if (child_pid == -1)
        {
            perror("fork");
            continue;
        }

        if (child_pid == 0)
        {
            char *argv[2];
            argv[0] = line;
            argv[1] = NULL;

            if (execve(line, argv, environ) == -1)
            {
                perror(line);
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            wait(&status);
        }
    }

    free(line);
    return (0);
}
