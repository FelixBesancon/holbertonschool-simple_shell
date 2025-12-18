#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

extern char **environ;

int main(void)
{
    pid_t child_pid;
    int status;
    int i;

    for (i = 0; i < 5; i++)
    {
        child_pid = fork();
        if (child_pid == -1)
        {
            perror("Error:");
            return (1);
        }

        if (child_pid == 0)
        {
            char *argv[] = {"/bin/ls", "-l", "/tmp", NULL};
            if (execve(argv[0], argv,  environ) == -1)
            {
                perror("Error:");
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            wait(&status);
        }
    }

    return (0);
}
