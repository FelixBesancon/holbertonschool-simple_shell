#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(void)
{
	int count = 0;
	pid_t PID;
	char *args[] = {"ls", "-l", "/tmp", NULL};

	PID = getpid();
	printf("PPID is %u\n", PID);
	while (count < 5)
	{
		PID  = fork();
		if (PID == -1)
		{
			perror("fork");
			return (-1);
		}
		if (PID == 0)
		{
			PID = getpid();
			printf("PID is %u\n", PID);
			execve("/bin/ls", args, NULL);
			perror("execve");
			exit(1);
		}
		else
		{
			wait(NULL);
			PID = getpid();
			printf("PPID is %u\n", PID);
			count++;
		}
	}
	return (0);
}
