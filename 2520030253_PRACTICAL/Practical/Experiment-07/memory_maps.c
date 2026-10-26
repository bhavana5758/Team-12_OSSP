
#include <stdio.h>
#include <unistd.h>

int main() {
    char path[100];

    printf("Process ID: %d\n", getpid());
    snprintf(path, sizeof(path), "/proc/%d/maps", getpid());

    FILE *fp = fopen(path, "r");
    if (fp == NULL) {
        perror("fopen");
        return 1;
    }

    char line[256];
    while (fgets(line, sizeof(line), fp))
        printf("%s", line);

    fclose(fp);
    return 0;
}


