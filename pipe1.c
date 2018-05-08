#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define BUF_SIZE 20

int main(int argc, char **argv)
{
	int fds[2];
	char message[] = "Who are you\n";
	char buf[BUF_SIZE];
	pid_t pid;

	pipe(fds);
	pid = fork();
	if (pid == 0) {
		write(fds[1], message, strlen(message));
		fputs("I am a child process\n", stdout);
	} else {
		fputs("I am a parent process\n", stdout);
		read(fds[0], buf, BUF_SIZE);
		fputs(buf, stderr);
	}

	fputs("End of process\n", stdout);
	return 0;
}
	
