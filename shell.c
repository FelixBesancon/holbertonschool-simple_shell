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
	ssize_t read_chars;

	read_chars = getline(line, len, stdin);
	if (read_chars == -1)
		return (-1);

	if (read_chars > 0 && (*line)[read_chars - 1] == '\n')
		(*line)[read_chars - 1] = '\0';

	if ((*line)[0] == '\0')
		return (0);

	return (read_chars);
}

/**
 * execute_cmd - executes a command
 * @line: command line
 * @prog_name: argv[0]
 * @env: environment
 */
/*
void execute_cmd(char *line, char *prog_name, char **env)
{
	static int line_nb = 1;
	char *argv[30], *token, *full_path;
	int index = 0, status;
	pid_t pid;

	token = strtok(line, " \t");
	while (token != NULL && index < 30)
	{
		argv[index++] = token;
		token = strtok(NULL, " \t");
	}
	argv[index] = NULL;
	if (index == 0)
		return;
	if (execute_builtin(argv, env, line) != 0)
		return;
	full_path = get_full_path(argv[0], env);
	if (full_path == NULL)
	{
		fprintf(stderr, "%s: %d: %s: not found\n",
			prog_name, line_nb, argv[0]);
		line_nb++;
		return;
	}
	pid = fork();
	if (pid == -1)
	{
		perror(prog_name);
		free(full_path);
		line_nb++;
		return;
	}
	if (pid == 0)
	{
		if (execve(full_path, argv, env) == -1)
		{
			fprintf(stderr, "%s: %d: %s: not found\n",
				prog_name, line_nb, argv[0]);
			free(full_path);
			_exit(127);
		}
	}
	else
	{
		wait(&status);
		last_status = status >> 8;
	}
	free(full_path);
	line_nb++;
}
*/
void execute_cmd(char *line, char *prog_name, char **env, int *last_status)
{
	static int line_nb = 1;
	char *argv[30];
	int argc;

	argc = tokenize_line(line, argv, 30);
	if (argc == 0)
		return;

	if (execute_builtin(argv, env, line, last_status) != 0)
		return;

	run_command(argv, prog_name, env, &line_nb, last_status);
}

int tokenize_line(char *line, char **argv, int max_args)
{
	char *token;
	int index = 0;

	token = strtok(line, " \t");
	while (token != NULL && index < max_args - 1)
	{
		argv[index++] = token;
		token = strtok(NULL, " \t");
	}
	argv[index] = NULL;

	return (index);
}

void run_command(char **argv, char *prog_name, char **env, int *line_nb, int *last_status)
{
	char *full_path;
	int status;
	pid_t pid;

	full_path = get_full_path(argv[0], env);
	if (full_path == NULL)
	{
		fprintf(stderr, "%s: %d: %s: not found\n",
				prog_name, *line_nb, argv[0]);
		(*line_nb)++;
		return;
	}

	pid = fork();
	if (pid == -1)
	{
		perror(prog_name);
		free(full_path);
		(*line_nb)++;
		return;
	}

	if (pid == 0)
	{
		if (execve(full_path, argv, env) == -1)
		{
			fprintf(stderr, "%s: %d: %s: not found\n",
					prog_name, *line_nb, argv[0]);
			free(full_path);
			_exit(127);
		}
	}
	else
	{
		wait(&status);
		*last_status = status >> 8;
	}

	free(full_path);
	(*line_nb)++;
}
