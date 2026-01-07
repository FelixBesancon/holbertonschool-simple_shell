#include "shell.h"

/**
 * get_full_path - find full path of a command using PATH
 * @cmd: command name
 * @env: environment
 *
 * Return: malloc full path or NULL
 */
char *get_full_path(char *cmd, char **env)
{
	char *path_cpy;
	int index;

	if (!cmd)
		return (NULL);
	if (strchr(cmd, '/'))
	{

		if (access(cmd, X_OK) == 0)
			return (strdup(cmd));
		return (NULL);
	}

	for (index = 0; env[index] != NULL; index++)
	{
		if (strncmp(env[index], "PATH=", 5) == 0)
			path_cpy = strdup(env[index] + 5);
	}
	if (!path_cpy)
		return (NULL);
	return (find_in_path(path_cpy, cmd));
}

/**
 * find_in_path - search command in PATH directories
 * @path_cpy: copy of PATH environment variable
 * @cmd: command name
 *
 * Return: malloc full path or NULL
 */
char *find_in_path(char *path_cpy, char *cmd)
{
	char *token, *full_path;
	int len;

	if (!path_cpy)
		return (NULL);
	token = strtok(path_cpy, ":");
	while (token)
	{
		len = strlen(token) + strlen(cmd) + 2;
		full_path = malloc(len);
		if (!full_path)
			break;
		strcpy(full_path, token);

		strcat(full_path, "/");
		strcat(full_path, cmd);
		if (access(full_path, X_OK) == 0)
		{
			free(path_cpy);
			return (full_path);
		}
		free(full_path);
		token = strtok(NULL, ":");
	}
	free(path_cpy);
	return (NULL);
}
