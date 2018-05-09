#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1014

int main(int argc, char **argv)
{
	int readdup, writedup;
	int serv_sock, clnt_sock;
	char buf[BUF_SIZE] = {0};
	FILE *readfd, *writefd;
	struct sockaddr_in serv_addr, clnt_addr;
	socklen_t clnt_len;

	if (argc != 2) {
		printf("Usage:%s <PORT>\n", argv[0]);
		exit(1);
	}

	serv_sock = socket(AF_INET, SOCK_STREAM, 0);
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(atoi(argv[1]));

	bind(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
	listen(serv_sock, 5);
	
	clnt_len = sizeof(clnt_addr);
	clnt_sock = accept(serv_sock, (struct sockaddr *)&serv_addr, &clnt_len);
	readdup = clnt_sock;
	writedup = dup(clnt_sock);

	readfd = fdopen(readdup, "r");
	writefd = fdopen(writedup, "w");

	fputs("From Server:Hi, client?\n", writefd);
	fputs("I love all of the world\n", writefd);
	fputs("You are awesome!\n", writefd);
	fflush(writefd);

	shutdown(fileno(writefd), SHUT_WR);
	fclose(writefd);

	fgets(buf, BUF_SIZE, readfd);
	fputs(buf, stdout);
	fflush(stdout);
	fclose(readfd);
	return 0;
}

