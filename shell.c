#include "shell.h"

/**
 * display_prompt - Affiche le prompt pour mode interactif
 */
void display_prompt(void)
{
	if (isatty(STDIN_FILENO))
	{
		printf("#cisfun$ ");
		fflush(stdout);
	}
}

/**
 * execute_cmd - fork et execve la commande
 * @line: ligne de commande
 * @program_name: argv[0] pour erreur
 * @env: variable d environnement
 */
void execute_cmd(char *line, char *program_name, char **env)
{
	pid_t child_pid;
	char *cmd_argv[2];
	int status;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror(program_name);
		return;
	}

	if (child_pid == 0)
	{
		cmd_argv[0] = line;
		cmd_argv[1] = NULL;
		if (execve(line, cmd_argv, env) == -1)
		{
			perror(program_name);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(&status);
	}
}

/**
 * read_line - lit une ligne depuis stdin
 * @line: pointeur vers buffer
 * @bufsize: taille du buffer
 * Return: longueur de ligne ou -1 si EOF
 */
ssize_t read_line(char **line, size_t *bufsize)
{
	ssize_t len = getline(line, bufsize, stdin);

	if (len == -1)
		return (-1);

	if (len <= 1)
		return (0);

	if ((*line)[len - 1] == '\n')
		(*line)[len - 1] = '\0';

	if ((*line)[0] == '\0')
		return (0);

	return (len);
}
