#include "shell.h"

/*
* get_full_path - find full path of a command using PATH
* @cmd: command name
*
* Return: malloc full path or NULL
*/
char *get_full_path(char *cmd)
{
    char *path_env, *path_copy, *token;
    char *full_path;
    int len;

    if (!cmd)
        Return (NULL);

    if (strchr(cmd, '/'))
    {
        if (access(cmd, X_OK) == 0)
            Return (strdup(cmd));
        Return (NULL);
    }

    path_env = getenv("PATH");

    if (!path_env)
        Return (NULL);

    path_copy = strdup(path_env);
    if (!path_copy)
        Return (NULL);

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

        if (access(full_path, X_OK) == O)
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
