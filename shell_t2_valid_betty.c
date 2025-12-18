#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char **environ;

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
 * execute_cmd - Fork et execve la commande
 * @line: ligne de commande
 * @program_name: argv[0] pour erreur
 */
void execute_cmd(char *line, char *program_name)
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
		if (execve(line, cmd_argv, environ) == -1)
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
 * read_line - lit la ligne
 * @line: pointeur vers buffet
 * @bufsize: taille buffet
 * Return: longueur de  ligne ou -1 avec EOF
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

/**
 * main - Simple shell
 * @argc: nombre d'argument
 * @argv: tab d'arguments (argv[0] = nom du programme)
 * Return: 0 sur succès
 */
int main(int argc, char **argv)
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

		execute_cmd(line, argv[0]);
	}

	free(line);
	return (0);
}
