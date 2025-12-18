#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>

/* get_path_array - récup path sous forme de tableau */
char **get_path_array(void)
{
    char *path_env, *path_copy, *token;
    char **paths;
    int count, i;

    path_env = getenv("PATH");
    if (!path_env)
        return NULL;

    count = 1;
    for (i = 0; path_env[i]; i++)
        if (path_env[i] == ':')
            count++;

    path_copy = malloc(i + 1);
    if (!path_copy)
        return NULL;
    strcpy(path_copy, path_env);

    paths = malloc((count + 1) * sizeof(char *));
    if (!paths)
    {
        free(path_copy);
        return NULL;
    }

    i = 0;
    token = strtok(path_copy, ":");
    while (token)
    {
        paths[i++] = token;
        token = strtok(NULL, ":");
    }
    paths[i] = NULL;
    return paths;
}

/* main */
int main(int argc, char **argv)
{
    char **paths;
    char full_path[PATH_MAX];
    int i, found, arg;

    if (argc < 2)
    {
        printf("Usage: %s filename ...\n", argv[0]);
        return 1;
    }

    paths = get_path_array();
    if (!paths)
    {
        fprintf(stderr, "PATH not found\n");
        return 1;
    }

    for (arg = 1; arg < argc; arg++)
    {
        found = 0;
        for (i = 0; paths[i]; i++)
        {
            sprintf(full_path, "%s/%s", paths[i], argv[arg]);
            if (access(full_path, X_OK) == 0)
            {
                printf("%s\n", full_path);
                found = 1;
                break;
            }
        }
        if (!found)
            printf("%s: NOT FOUND\n", argv[arg]);
    }

    free(paths[0]); /* path_copy stoké dans le paths[0] */
    free(paths);
    return 0;
}
