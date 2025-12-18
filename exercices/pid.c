#include <unistd.h>
#include <stdio.h>

int main(void)
{
	pid_t my_pid, my_ppid;

	my_pid = getpid();
	my_ppid = getppid();
	printf("PID is: %u\nPPID is: %u\n", my_pid, my_ppid);
	return (0);
}
