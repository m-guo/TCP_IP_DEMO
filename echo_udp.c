#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024

void error_handle(char *message);

int main(int argc, char **argv)
{
	int sock_serv;
	int recv_len;
	char message[BUF_SIZE];
	socklen_t clnt_len;

	struct sockaddr_in serv_addr, clnt_addr;

	if (argc != 2) {
		printf("Usage:%s <PORT>\n", argv[0]);
		exit(1);
	}

	sock_serv = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock_serv == -1) {
		error_handle("socket() error");
		exit(1);
	}

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(atoi(argv[1]));

	if (bind(sock_serv, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1) {
		error_handle("bind() error");
		exit(1);
	}
	
	while (1) {	
		clnt_len = sizeof(clnt_addr);	
		recv_len = recvfrom(sock_serv, message, BUF_SIZE, 0, (struct sockaddr *)&clnt_addr, &clnt_len);
		if (!strcmp(message, "quit"))
			break;
		message[recv_len] = 0;
		printf("from clnt:%s\n", message);
		sendto(sock_serv, message, recv_len, 0, (struct sockaddr *) &clnt_addr, clnt_len);
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

