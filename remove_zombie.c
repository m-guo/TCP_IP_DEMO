#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>

void read_childpro(int sig)
{
    int status;
    pid_t pid;
    pid = waitpid(-1, &status, WNOHANG);
    if (WIFEXITED(status)) {
        printf("Removed child pro:%d\n", pid);
        printf("Child send:%d", WEXITSTATUS(status));
    }
}

int main(int argc, char **argv)
{
    pid_t pid;
    struct sigaction act;
    act.sa_handler = read_childpro;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;

    sigaction(SIGCHLD, &act, 0);

    pid = fork();
    if (pid == 0) {
        puts("Hi I am Child pro\n");
        sleep(5);
        exit(12);
    } else {
        printf("Child pid:%d\n", pid);
        pid = fork();
        if (pid == 0) {
            puts("Hi I am a Chiled Pro\n");
            sleep(10);
            exit(24);
        } else {
            printf("Chiled pid:%d\n", pid);

            for (int i = 0; i < 5; i++) {
                puts("Wait...\n");
                sleep(5);
            }
        }
    }
}