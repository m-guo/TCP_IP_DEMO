#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv)
{
	int cfd1, cfd2;
	char input_dup[] = "intented input dup\n";
	char input_dup2[] = "intented intput dup2\n";
	char input_out[] = "intented output\n";

	cfd1 = dup(1);
	cfd2 = dup2(cfd1, 7);

	printf("fd1: %d, fd2: %d\n", cfd1, cfd2);
	write(cfd1, input_dup, strlen(input_dup));
	write(cfd2, input_dup2, strlen(input_dup2));

	close(cfd1);
	close(cfd2);
	
	write(1, input_out, strlen(input_out));
	close(1);
	write(1, input_out, strlen(input_out));

	return 0;
}
	
