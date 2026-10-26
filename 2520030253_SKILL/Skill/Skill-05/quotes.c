#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char input[200];

    printf("Enter text: ");
    if (fgets(input, sizeof(input), stdin) == NULL)
        return 1;

    input[strcspn(input, "\n")] = '\0';

    if (input[0] == '\'') {
        printf("Single quoted: ");
        printf("%s\n", input + 1);
    } else if (input[0] == '"') {
        printf("Double quoted: ");
        printf("%s\n", input + 1);
    } else {
        printf("Text: %s\n", input);
    }

    return 0;
}
