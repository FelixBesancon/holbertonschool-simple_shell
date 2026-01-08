#include "shell.h"

/**
 * execute_builtin - executes a built-in command
 * @argv: the argument to test and execute if it is a built-in
 * @env: environment
 * @line: command line
 * @last_status: status of the last command
 *
 * Return: 1 if argv is a built-in, 0 otherwise
 */
int execute_builtin(char **argv, char **env, char **line, int *last_status)
{
	int index;

	if (strcmp(argv[0], "exit") == 0)
	{
		free(*line);
		*line = NULL;
		exit(*last_status);
	}

	if (strcmp(argv[0], "env") == 0)
	{
		for (index = 0; env[index] != NULL; index++)
			printf("%s\n", env[index]);
		return (1);
	}
	return (0);
}
