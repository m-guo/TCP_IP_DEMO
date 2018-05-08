#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>

void error_handle(char *message);

int main(int argc, char **argv)
{
	int sock;
	int snd_buf, rcv_buf, state;
	socklen_t len;

	sock = socket(AF_INET, SOCK_STREAM, 0);
	len = sizeof(snd_buf);
	
	state = getsockopt(sock, SOL_SOCKET, SO_SNDBUF, (void *)&snd_buf, &len);
	// snd_buf = 1024 * 1024 * 2;
	//state = setsockopt(sock, SOL_SOCKET, SO_SNDBUF, (void *)&snd_buf, sizeof(snd_buf));

	if (state)
		error_handle("getsockopt() error");

	state = getsockopt(sock, SOL_SOCKET, SO_RCVBUF, (void *)&rcv_buf, &len);
	//rcv_buf = 1024 * 1024;
	//state = setsockopt(sock, SOL_SOCKET, SO_RCVBUF, (void *)&rcv_buf, sizeof(rcv_buf));

	if (state)
		error_handle("getsockopt() error");

	printf("Input buffer size:%d\n", snd_buf);
	printf("Output buffer size:%d\n", rcv_buf);

	return 0;
}

void error_handle(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}

