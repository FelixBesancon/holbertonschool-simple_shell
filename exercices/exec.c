#include <stdio.h>
#include <unistd.h>

extern char **environ;

int main(void)
{
    char *argv[] = {"/bin/ls", "-l", "/usr/", NULL};

    printf("Before execve\n");
    execve(argv[0], argv, environ);
    perror("execve");
    return (0);
}
