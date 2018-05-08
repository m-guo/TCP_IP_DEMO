#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 30
void error_handle(char *message);
void read_childpro(int sig);

int main(int argc, char **argv)
{
	int sock_serv, sock_clnt;
	int str_len;
	struct sockaddr_in serv_addr, clnt_addr;
	socklen_t clnt_len;
	
	pid_t pid;
	struct sigaction act;
	int state;
	char buf[BUF_SIZE];
	
	if (argc != 2) {
		printf("Usage: %s <PORT> \n", argv[0]);
		exit(1);
	}

	act.sa_handler = read_childpro;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;

	state = sigaction(SIGCHLD, &act, 0);
	
	sock_serv = socket(AF_INET, SOCK_STREAM, 0);
	
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(atoi(argv[1]));

	if (bind(sock_serv, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1) {
		error_handle("bind() error");
	}

	if (listen(sock_serv, 5) == -1) {
		error_handle("listen() error");
	}
	
	while (1) {
		//sock_clnt = accept(sock_serv, (struct sockaddr *)&clnt_addr, &clnt_len);
		sock_clnt = accept(sock_serv, (struct sockaddr *)&clnt_addr, &clnt_len);
		if (sock_clnt == -1) {
			continue;
		} else {
			puts("new Client Connected ...");
		}
		pid = fork();
		if (pid == -1) {
			close(sock_serv);
			continue;
		}
		if (pid == 0) {
			close(sock_serv);
			while ((str_len = read(sock_clnt, buf, BUF_SIZE)) != 0) {
				write(sock_clnt, buf, str_len);
			}
			close(sock_clnt);
			puts("client disconnected...");
			return 0;
		} else {
			close(sock_clnt);
		}
	}
	close(sock_serv);
	return 0;
}

void read_childpro(int sig)
{
	pid_t pid;
	int status;

	pid = waitpid(-1, &status, WNOHANG);
	printf("removeed proc id:%d \n", pid);
}

void error_handle(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
