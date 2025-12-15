#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main (void)
{
	char *line = NULL;
	size_t buffer = 0;
	ssize_t len;
	
	printf("$ ");
	len = getline(&line, &buffer, stdin);
	if (len != -1)
		printf("Command is: %s\nBuffer is: %zu\nLength is: %zd\n", line, buffer, len);
	else
		printf("\n");
	free(line);
	return (0);
}
