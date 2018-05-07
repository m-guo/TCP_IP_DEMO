#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define SUB_SIZE 30

void error_handld(char *message);

int main(int argc, char **argv)
{

	int sock_serv, sock_clnt;
	int read_cunt;
	char buf[BUFSIZ];
	FILE *fd;
	
	struct sockaddr_in serv_addr;

	if (argc != 2) {
		printf("Usage:%s <PORT>\n", argv[0]);
		exit(1);
	}
	fd = fopen("file_server.c", "rb");

	sock_serv = socket(AF_INET, SOCK_STREAM, 0);
	if (sock_serv == -1) {
		error_handld("socket() error");
	}

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htons(INADDR_ANY);
	serv_addr.sin_port = htons(atoi(argv[1]));
	
	if (bind(sock_serv, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1) {
		error_handld("bind() error");
	}
	
	if (listen(sock_serv, 5) == -1)
		error_handld("listen() error");

	sock_clnt = accept(sock_serv, (struct sockaddr *)NULL, NULL);
	
	while (1) {
		read_cunt = fread((char *)buf, 1, BUFSIZ, fd);
		if (read_cunt < BUFSIZ) {
			write(sock_clnt, buf, read_cunt);
			break;
		}
		write(sock_clnt, buf, BUFSIZ);
	}
	 
	shutdown(sock_clnt, SHUT_WR);
	read(sock_clnt, buf, BUFSIZ);
	printf("Message from client: %s\n", buf);
	
	fclose(fd);
	close(sock_clnt);
	close(sock_serv);
	return 0;
}

void error_handld(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}

