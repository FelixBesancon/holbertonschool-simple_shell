#include "shell.h"

/**
 * main - entry point of the shell
 * @argc: argument count
 * @argv: argument vector
 * @env: environment
 * Return: 0
 */
int main(int argc, char **argv, char **env)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;

	(void)argc;

	while (1)
	{
		display_prompt();
		read = read_line(&line, &len);

		if (read == -1)
		{
			if (isatty(STDIN_FILENO))
				printf("\n");
			break;
		}

		if (read == 0)
			continue;

		execute_cmd(line, argv[0], env);
	}

	free(line);
	return (0);
}
