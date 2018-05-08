#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main()
{
	int fds[2];
	char buf[100] = {0};
	int str_len;
	pid_t pid;
	FILE *fd;
	
	pipe(fds);
	pid = fork();
	if (pid == 0) {
		//sleep(10);
		str_len = read(fds[0], buf, 100);
		fd = fopen("read_write.txt", "w+");
		fwrite((char *)buf, 1, str_len, fd);	
		fputs("I have wirte in file\n", stdout);
		return 0;
	} else {
		fgets(buf, 100, stdin);
		write(fds[1], buf, strlen(buf));
		fputs("I have input something\n", stdout);
		sleep(2);
	}
	return 0;
}

