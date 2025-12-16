#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(void)
{
	int ac;
	pid_t PID;
	char *line = NULL, *token = NULL, **av = NULL;
	size_t buffer = 0;
	ssize_t len;
	
	while (1)
	{
		printf("super_simple_shell$ ");
		len = getline(&line, &buffer, stdin);
		if (len == -1)
		{
			printf("\n");
			break;
		}
		else
		{
			av = malloc(buffer * sizeof(char*));
			token = strtok(line, " \n");
			for (ac = 0; token != NULL; ac++)
			{
				av[ac] = token;
				token = strtok(NULL, " \n");
			}
			av[ac] = NULL;
			PID = fork();
			if (PID == -1)
			{
				perror("fork");
				return (-1);
			}
			if (PID == 0)
			{
				execve(av[0], av, NULL);
				perror("execve");
				exit(1);
			}
			else
				wait(NULL);
			free(av);
		}
	}
	free(line);
	return (0);
}