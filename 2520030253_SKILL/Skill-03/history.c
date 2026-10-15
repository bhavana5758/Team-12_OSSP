
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char *line = NULL;
    size_t size = 0;
    char *history[100];
    int count = 0, pos = 0;

    while (1) {
        printf("myshell> ");
        if (getline(&line, &size, stdin) == -1)
            break;

        line[strcspn(line, "\n")] = '\0';

        if (strcmp(line, "exit") == 0)
            break;

        if (strcmp(line, "history") == 0) {
            for (int i = 0; i < count; i++)
                printf("%d: %s\n", i + 1, history[i]);
            continue;
        }

        if (strcmp(line, "prev") == 0) {
            if (pos > 0) pos--;
            if (count > 0) printf("%s\n", history[pos]);
            continue;
        }

        if (strcmp(line, "next") == 0) {
            if (pos < count - 1) pos++;
            if (count > 0) printf("%s\n", history[pos]);
            continue;
        }

        if (strlen(line) > 0 && count < 100) {
            history[count] = strdup(line);
            if (history[count] == NULL) break;
            count++;
            pos = count - 1;
            printf("Saved: %s\n", line);
        }
    }

    for (int i = 0; i < count; i++)
        free(history[i]);

    free(line);
    return 0;
}
