#include "shell.h"

/**
 * execute_builtin - executes a built-in command
 * @argv: the argument to test and execute if it is a built-in
 * @env: environment
 *
 * Return: 1 if argv is a built-in, 0 otherwise
 */
int execute_builtin(char **argv, char **env)
{
	int index;
	char *current_env;

	if (strcmp(argv[0], "exit") == 0)
		exit(0);

	if (strcmp(argv[0], "env") == 0)
	{
		for (index = 0; env[index] != 0; index++)
		{
			current_env = env[index];
			printf("%s\n", current_env);
		}
		printf("\n");
		return (1);
	}
	return (0);
}
