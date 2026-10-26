#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s command [arguments]\n", argv[0]);
        return 1;
    }

    char *path = getenv("PATH");
    if (path == NULL) {
        printf("PATH not found\n");
        return 1;
    }

    char *copy = strdup(path);
    if (copy == NULL) return 1;

    char *dir = strtok(copy, ":");
    char fullpath[512];

    while (dir != NULL) {
        snprintf(fullpath, sizeof(fullpath), "%s/%s", dir, argv[1]);

        if (access(fullpath, X_OK) == 0) {
            pid_t pid = fork();

            if (pid == 0) {
                execv(fullpath, &argv[1]);
                perror("execv");
                exit(1);
            }

            if (pid > 0) waitpid(pid, NULL, 0);
            else perror("fork");

            free(copy);
            return 0;
        }

        dir = strtok(NULL, ":");
    }

    printf("Command not found: %s\n", argv[1]);
    free(copy);
    return 1;
}
