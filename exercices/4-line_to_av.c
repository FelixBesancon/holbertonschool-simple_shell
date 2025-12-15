#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	int ac = 0;
	char **av, str[] = "The line to cut.", *str_token = NULL;

	av = malloc(5 * sizeof(char *));
	printf("%s\n", str);
	str_token = strtok(str, " .\n");
	while (str_token != NULL)
	{
		av[ac] = str_token;
		printf("%s\n", av[ac]);
		ac++;
		str_token = strtok(NULL, " .\n");
	}
	av[ac] = NULL;
	free(av);
	return (0);
}
