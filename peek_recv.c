#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main(int argc, char **argv)
{
	int sock_serv, sock_cnlt;
	socklen_t clnt_len;
	struct sockaddr_in serv_addr, clnt_addr;
	char buf[30] = {0};
	int str_len;

	if (argc != 2) {
		printf("Usage: %s <PORT>\n", argv[0]);
		exit(1);
	}

	sock_serv = socket(AF_INET, SOCK_STREAM, 0);
	
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(atoi(argv[1]));

	bind(sock_serv, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
	
	listen(sock_serv, 5);
	
	clnt_len = sizeof(clnt_addr);
	sock_cnlt = accept(sock_serv, (struct sockaddr *)&clnt_addr, &clnt_len);

	while (1) {
		str_len = recv(sock_cnlt, buf, 30, MSG_PEEK|MSG_DONTWAIT);
		if (str_len > 0)
			break;
	}

	buf[str_len] = 0;
	printf("Buffering %d, bytes: %s\n", str_len, buf);

	str_len = recv(sock_cnlt, buf, 30, 0);
	buf[str_len] = 0;
	printf("Read again:%s \n", buf);
	close(sock_serv);
	close(sock_cnlt);
	return 0;
}

		

