
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int *data = malloc(5 * sizeof(int));
    if (data == NULL) return 1;

    for (int i = 0; i < 5; i++)
        data[i] = i + 1;

    printf("Parent before fork: %d\n", data[0]);
    fflush(stdout);

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        free(data);
        return 1;
    }

    if (pid == 0) {
        data[0] = 100;
        printf("Child modified value: %d\n", data[0]);
        fflush(stdout);
        free(data);
        _exit(0);
    }

    wait(NULL);
    printf("Parent after child: %d\n", data[0]);

    free(data);
    return 0;
}
