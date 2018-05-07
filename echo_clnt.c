#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

void error_handle(char *message);

int main(int argc, char **argv)
{
	int serv_sock;
	int str_len, accept_len, recv_len;
	char message[1024];

	struct sockaddr_in serv_addr;

	if (argc != 3) {
		printf("Usage: %s <ADDR> <PORT> \n", argv[0]);
		exit(1);
	}

	serv_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (serv_sock == -1)
		error_handle("socket() error");

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
	serv_addr.sin_port = htons(atoi(argv[2]));

	if (connect(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1) {
		error_handle("connect() error");
	}
	
	while (1) {
		fputs("Input message(Q to quit): \n", stdout);
		fgets(message, 1024, stdin);
		if (!strcmp(message, "q\n") || !strcmp(message, "Q\n"))
			break;	
		write(serv_sock, message, strlen(message));
		accept_len = strlen(message);

		str_len = 0;
		while (str_len < accept_len) {
			recv_len = read(serv_sock, message, 1024);
			str_len += recv_len;
		}
		message[str_len-1] = 0;
		printf("%d len from server of \"%s\" \n", str_len, message);
	}
	//at this step client send server message, it close the TCP connect	
	close(serv_sock);
	return 0; 

}

void error_handle(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
