#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>

void error_handle(char *message);

int main(int argc, char **argv)
{
	int sock_serv;
	int recv_len;
	socklen_t from_len;

	char message[1024];

	struct sockaddr_in serv_addr, from_addr;

	if (argc != 3) {
		printf("Usage: %s <ADDR> <PORT>\n", argv[0]);
		exit(1);
	}
	
	sock_serv = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock_serv == -1) {
		error_handle("socket() error");
		exit(1);
	}

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
	serv_addr.sin_port = htons(atoi(argv[2]));

	while (1) {
		fputs("Insert message(q to quit): \n", stdout);
		fgets(message, sizeof(message), stdin);
		if (!strcmp(message, "q\n") || !strcmp(message, "Q\n"))
			break;
		sendto(sock_serv, message, strlen(message), 0, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
		from_len = sizeof(from_addr);
		recv_len = recvfrom(sock_serv,  message, 1024, 0, (struct sockaddr *)&from_addr, &from_len);
		message[recv_len] = 0;
		printf("recv from server:%s\n", message);
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
	
