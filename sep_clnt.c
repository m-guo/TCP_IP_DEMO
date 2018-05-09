#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024

int main(int argc, char **argv)
{
	int serv_sock;
	struct sockaddr_in serv_addr;
	char buf[BUF_SIZE] = {0};

	FILE *readfd;
	FILE *writefd;

	if (argc != 3) {
		printf("Usage:%s <IP> <PORT> \n", argv[0]);
		exit(1);
	}

	serv_sock = socket(AF_INET, SOCK_STREAM, 0);
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
	serv_addr.sin_port = htons(atoi(argv[2]));

	connect(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

	readfd = fdopen(serv_sock, "r");
	writefd = fdopen(serv_sock, "w");

	while (1) {
		if (fgets(buf, BUF_SIZE, readfd) == NULL)
			break;
		fputs(buf, stdout);
		fflush(stdout);
	}

	fputs("From Client: Thank you! \n", writefd);
	fflush(writefd);
	fclose(writefd);
	fclose(readfd);
	return 0;
}

