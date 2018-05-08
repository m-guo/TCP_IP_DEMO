#include <stdio.h>
#include <unistd.h>
#include <string.h>


#define BUF_SIZE 30

int main(int argc, char **argv)
{
	char buf[BUF_SIZE];
	char ch_message[] = "How are you\n";
	char pa_maessage[] = "Thank you for your message\n";
	int fds[2], fdt[2];
	pid_t pid;

	pipe(fds);
	pipe(fdt);
	pid = fork();
	if (pid == 0) {
		write(fds[1], ch_message, strlen(ch_message));
		//sleep(2);
		//fputs("I am child process\n", stdout);
		read(fdt[0], buf, BUF_SIZE);
		fputs(buf, stdout);
	} else {
		read(fds[0], buf, BUF_SIZE);
		fputs(buf, stdout);
		write(fdt[1], pa_maessage, strlen(pa_maessage));
		//fputs("I am parent process\n", stdout);
		sleep(3);
	}

	return 0;
}

