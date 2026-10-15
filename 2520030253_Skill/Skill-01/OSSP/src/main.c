#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_COMMAND 100

int main() {
    char command[MAX_COMMAND];

    printf("Enter Linux Command: ");
    fflush(stdout);

    if (fgets(command, sizeof(command), stdin) == NULL) {
        printf("Failed to read command.\n");
        return 1;
    }

    command[strcspn(command, "\n")] = '\0';

    if (strlen(command) == 0) {
        printf("No command entered.\n");
        return 1;
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return 1;
    }

    if (pid == 0) {
        printf("Child Process\n");
        printf("Child PID = %d\n", getpid());

        execlp(command, command, (char *)NULL);

        perror("exec failed");
        exit(1);
    }

    printf("Parent Process\n");
    printf("Parent PID = %d\n", getpid());
    printf("Child PID = %d\n", pid);

    wait(NULL);

    printf("Child Process Completed\n");

    return 0;
}
