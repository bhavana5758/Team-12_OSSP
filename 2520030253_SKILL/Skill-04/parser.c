#include <stdio.h>
#include <string.h>

int main(void) {
    char input[200];

    printf("Enter a command: ");

    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 1;
    }

    input[strcspn(input, "\n")] = '\0';

    char *token = strtok(input, " \t");

    while (token != NULL) {
        printf("Token: %s\n", token);
        token = strtok(NULL, " \t");
    }

    return 0;
}
