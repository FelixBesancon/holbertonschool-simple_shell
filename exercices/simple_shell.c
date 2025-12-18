#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char **environ;


int main(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;
    pid_t child_pid;
    int status, ac;

    while (1)
    {
        printf("#cisfun$ ");
        nread = getline(&line, &len, stdin);
        
        /* gestion EOF (Ctrl+D) */
        if (nread == -1)
        {
            printf("\n");
            break;
        }

        /* Ignorer les lignes vide */
        if (nread <= 1)
            continue;

        /* retirer le '\n' à la fin */
        if (line[nread - 1] == '\n')
            line[nread - 1] = '\0';

        /* Alloc pour les argument */
        char **argv = malloc((nread + 1) * sizeof(char *));
        if (!argv)
        {
            perror("malloc");
            continue;
        }

        /* decoupe la ligne en arguments */
        char *token = strtok(line, " \t\n");
        ac = 0;
        while (token != NULL)
        {
            argv[ac++] = token;
            token = strtok(NULL, " \t\n");
        }
        argv[ac] = NULL;

        /* vérifie qu'on a bien une commande */
        if (argv[0] == NULL)
        {
            free(argv);
            continue;
        }

        /* gestion de la commande exit */
        if (strcmp(argv[0], "exit") == 0)
        {
            free(argv);
            break;
        }

        /* fork + execve + wait */
        child_pid = fork();
        if (child_pid == -1)
        {
            perror("fork");
            free(argv);
            continue;
        }

        if (child_pid == 0)
        {
            /* processus enfant */
            if (execve(argv[0], argv, environ) == -1)
            {
                perror("execve");
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            /* processus parent */
            wait(&status);
        }

        free(argv);
    }

    free(line);
    return (0);
}