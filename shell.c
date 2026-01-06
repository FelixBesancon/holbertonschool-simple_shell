#include "shell.h"

/**
 * display_prompt - prints the prompt
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
 * read_line - reads a line from stdin
 * @line: buffer
 * @len: buffer size
 * Return: number of chars read
 */
ssize_t read_line(char **line, size_t *len)
{
	ssize_t read;

	read = getline(line, len, stdin);
	if (read == -1)
		return (-1);

	if (read > 0 && (*line)[read - 1] == '\n')
		(*line)[read - 1] = '\0';

	if ((*line)[0] == '\0')
		return (0);

	return (read);
}

/**
 * execute_cmd - executes a command
 * @line: command line
 * @prog_name: argv[0]
 * @env: environment
 */
void execute_cmd(char *line, char *prog_name, char **env)
{
	static int line_nb = 1;
	pid_t pid;
	char *argv[30];
	char *token;
	int i = 0, is_builtin = 0;
	int status;

	token = strtok(line, " \t");
	while (token != NULL && i < 30)
	{
		argv[i] = token;
		token = strtok(NULL, " \t");
		i++;
	}
	argv[i] = NULL;
	if (i == 0)
		return;
	is_builtin = execute_builtin(argv, env);
	if (is_builtin != 0)
		return;
	pid = fork();
	if (pid == -1)
	{
		perror(prog_name);
		return;
	}
	if (pid == 0)
	{
		if (execve(argv[0], argv, env) == -1)
		{
			fprintf(stderr, "%s: %d: %s: not found\n",
				prog_name, line_nb, argv[0]);
			exit(127);
		}
	}
	else
		wait(&status);
	line_nb++;
}
