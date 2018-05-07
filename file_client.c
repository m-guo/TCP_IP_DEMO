#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 30

void error_handle(char *message);

int main(int argc, char **argv)
{
	int sock_serv;
	int recv_len;
	char buf[BUF_SIZE];
	FILE *fd;
	
	struct sockaddr_in serv_addr;

	if (argc != 3) {
		printf("Usage: %s <ADDR> <PORT> \n", argv[0]);
		exit(1);
	}

	fd = fopen("receive.dat", "w+");
	if (fd == NULL)
		error_handle("fopne() error");

	sock_serv = socket(AF_INET, SOCK_STREAM, 0);
	if (sock_serv == -1)
		error_handle("socket() error");

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
	serv_addr.sin_port = htons(atoi(argv[2]));

	if (connect(sock_serv, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1) {
		error_handle("connect() error");
	}

	while (recv_len = read(sock_serv, buf, BUF_SIZE))
		fwrite((void *)buf, 1, BUF_SIZE, fd);

	fputs("Recieve file data", stdout);
	write(sock_serv, "Thank you", 10);
	close(sock_serv);
	fclose(fd);

	return 0;
}

void error_handle(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
