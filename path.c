#include "shell.h"

/**
 * get_full_path - find full path of a command using PATH
 * @cmd: command name
 *
 * Return: malloc full path or NULL
 */
char *get_full_path(char *cmd)
{
    char *path_env;

    if (!cmd)
        return (NULL);
    if (strchr(cmd, '/'))
    {

        if (access(cmd, X_OK) == 0)
            return (strdup(cmd));
        return (NULL);
    }
    path_env = getenv("PATH");
    if (!path_env)
        return (NULL);
    return (find_in_path(path_env, cmd));
}

/**
 * find_in_path - search command in PATH directories
 * @path_env: PATH environment variable
 * @cmd: command name
 *
 * Return: malloc full path or NULL
 */
char *find_in_path(char *path_env, char *cmd)
{
    char *path_copy, *token, *full_path;
    int len;

    path_copy = strdup(path_env);
    if (!path_copy)
        return (NULL);
    token = strtok(path_copy, ":");
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
            free(path_copy);
            return (full_path);
        }
        free(full_path);
        token = strtok(NULL, ":");
    }
    free(path_copy);
    return (NULL);
}
