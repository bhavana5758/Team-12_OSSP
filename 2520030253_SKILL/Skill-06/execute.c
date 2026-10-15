#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(void) {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return 1;
    }

    if (pid == 0) {
        char *args[] = {"ls", "-l", NULL};
        execvp(args[0], args);
        perror("exec failed");
        exit(1);
    } else {
        waitpid(pid, NULL, 0);
        printf("Child process completed.\n");
    }

    return 0;
}
