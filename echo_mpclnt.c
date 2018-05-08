#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 30
void error_handle(char *message);
void read_routine(int sock, char *buf);
void write_routine(int sock, char *buf);

int main(int argc, char **argv)
{
	int sock_serv;
	struct sockaddr_in serv_addr;

	pid_t pid;
	char buf[BUF_SIZE];

	if (argc != 3) {
		printf("Usage:%s <IP> <PORT> \n", argv[0]);
		exit(1);
	}

	sock_serv = socket(AF_INET, SOCK_STREAM, 0);
	
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
	serv_addr.sin_port = htons(atoi(argv[2]));

	if(connect(sock_serv, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1) {
		error_handle("connect() error");
	}

	pid = fork();
	if (pid == 0) {
		write_routine(sock_serv, buf);
	} else {
		read_routine(sock_serv, buf);
	}

	close(sock_serv);
	return 0;
}

void error_handle(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}

void write_routine(int sock, char *buf)
{
	while (1) {
		fgets(buf, BUF_SIZE, stdin);
		if (!strcmp(buf, "q\n") || !strcmp(buf, "Q\n")) {
			shutdown(sock, SHUT_WR);
			return ;
		}
		write(sock, buf, strlen(buf));
	}
}

void read_routine(int sock, char *buf)
{
	int str_len;

	while (1) {
		if (str_len = read(sock, buf, BUF_SIZE)) {
			buf[str_len] = 0;
			printf("Message from server: %s", buf);
		}
		return ;
	}
}

