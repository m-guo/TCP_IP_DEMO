#include <stdio.h>
#include <unistd.h>

int main(int artc, char **argv)
{
	pid_t pid;
	pid = fork();
	if (pid == 0) {
		puts("Hi, I am a child process");
	} else {
		printf("Child Process ID: %d", pid);
		sleep(30);
	}

	if (pid == 0) {
		puts("End child process");
	} else {
		puts("End parent process");
	}
	return 0;
}

