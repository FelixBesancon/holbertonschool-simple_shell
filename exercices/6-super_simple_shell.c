#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

extern char **environ;

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
		if (len > 1)
		{
			if (len > 0 && line[len - 1] == '\n')
				line[len - 1] = '\0';
			av = malloc((len + 1) * sizeof(char *));
			if (av == NULL)
			{
				free(line);
				exit(1);
			}
			token = strtok(line, " \n\t");
			for (ac = 0; token != NULL; ac++)
			{
				av[ac] = token;
				token = strtok(NULL, " \n\t");
			}
			av[ac] = NULL;
			if (av[0] != NULL)
			{
				PID = fork();
				if (PID == -1)
				{
					perror("fork");
					free(av);
					free(line);
					return (1);
				}
				if (PID == 0)
				{
					execve(av[0], av, environ);
					perror("execve");
					exit(1);
				}
				else
					wait(NULL);
			}
			free(av);
		}
		else if (len == -1)
		{
			printf("\n");
			free(line);
			exit(0);
		}
	}
	free(line);
	return (0);
}
