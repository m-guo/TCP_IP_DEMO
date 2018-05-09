#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define BUF_SIZE 30
void error_handle(char *message);

int main(int argc, char **argv)
{
	int sock_serv;
	struct sockaddr_in recv_addr;

	if (argc != 3) {
		printf("Usage: %s <IP> <PORT> \n", argv[0]);
		exit(1);
	}

	sock_serv = socket(AF_INET, SOCK_STREAM, 0);
	memset(&recv_addr, 0, sizeof(recv_addr));
	recv_addr.sin_family = AF_INET;
	recv_addr.sin_addr.s_addr = inet_addr(argv[1]); 
	recv_addr.sin_port = htons(atoi(argv[2]));	


	if (connect(sock_serv, (struct sockaddr *)&recv_addr, sizeof(recv_addr)) == -1) {
		error_handle("connect() error");
	}

	write(sock_serv, "123", 3);
	send(sock_serv, "4", 1, MSG_OOB);
	write(sock_serv, "567", 3);
	send(sock_serv, "890", 3, MSG_OOB);
	close(sock_serv);
	return 0;
}

void error_handle(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}

