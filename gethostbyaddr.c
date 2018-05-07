#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>

void error_handle(char *message);

int main(int argc, char **argv)
{
	int i;
	struct sockaddr_in addr;
	struct hostent *host;

	if (argc != 2) {
		printf("Usage: %s <IP>\n", argv[0]);
		exit(1);
	}

	memset(&addr, 0, sizeof(addr));
	addr.sin_addr.s_addr = inet_addr(argv[1]);
	
	host = gethostbyaddr((char *)&addr.sin_addr, 4, AF_INET);
	if (!host)
		error_handle("gethostbyaddr ...error");

        printf("Officical name :%s \n", host->h_name);

        //结合性就是从做往右
        for (i = 0; (host->h_aliases)[i]; i++) {
                printf("aliases: %s\n", (host->h_aliases)[i]);
         }
/*
        pt = host->h_aliases;
        for (; *pt; pt++) {
             printf("alises:%s \n", *pt);
        }
*/
        printf("Address type: %s \n", (host->h_addrtype == AF_INET) ? "AF_INET    " : "AF_INET6");
        for (i = 0; host->h_addr_list[i]; i++) {
                printf("IP addr %d: %s \n", i+1, inet_ntoa(*(struct in_addr *)    host->h_addr_list[i]));

        }
        return 0;
}  

void error_handle(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}

