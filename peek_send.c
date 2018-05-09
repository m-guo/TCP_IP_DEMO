#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>


int main(int argc, char **argv)
{
	int sock_serv;
	char message[] = "Hi, I am from server";
	struct sockaddr_in serv_addr;

	if (argc != 3) {
		printf("Usage: %s <IP> <PORT> \n", argv[0]);
		exit(1);
	}

	sock_serv = socket(AF_INET, SOCK_STREAM, 0);

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET,
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
	serv_addr.sin_port = htons(atoi(argv[2]));

	connect(sock_serv, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

	write(sock_serv, message, strlen(message));

	close(sock_serv);
	return 0;
}
