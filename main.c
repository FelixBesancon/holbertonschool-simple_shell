#include "shell.h"

/**
 * main - Point d'entrée du shell
 * @argc: nombre d'arguments
 * @argv: tab d'arguments
 * @env: variable d'environnement
 * Return: 0 pour succès
 */
int main(int argc, char **argv, char **env)
{
	char *line = NULL;
	size_t bufsize = 0;
	ssize_t len;

	(void)argc;

	while (1)
	{
		display_prompt();
		len = read_line(&line, &bufsize);

		if (len == -1)
		{
			if (isatty(STDIN_FILENO))
				printf("\n");
			break;
		}

		if (len == 0)
			continue;

		execute_cmd(line, argv[0], env);
	}

	free(line);
	return (0);
}
