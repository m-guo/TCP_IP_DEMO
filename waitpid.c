#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char **argv)
{
    int state;
    pid_t pid;
    pid  = fork();

    if (pid == 0) {
        sleep(15);
        return 24;
    } else {
        while (!waitpid(pid, &state, WNOHANG)) {
            sleep(3);
            puts("sleep 3 secs\n");
        }
        if (WIFEXITED(state))
            printf("Child send: %d\n", WEXITSTATUS(state));
    }
    return 0;
}