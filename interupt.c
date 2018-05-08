#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void handle_interup(int sig)
{
	char message[5];
	if (sig == SIGINT) {
		fputs("Do you want to exit program\n", stdout);
		fgets(message, 4, stdin);
		if (!strcmp(message, "q\n") || ! strcmp(message, "Q\n"))
			exit(0);
	} else {
		sleep(10);
		return ;
	}
}

int main()
{
	signal(SIGINT, handle_interup);

	fputs("befor interupt ... \n", stderr);
	sleep(100);

	fputs("after interupt ... \n", stdout);
	return 0;
}

