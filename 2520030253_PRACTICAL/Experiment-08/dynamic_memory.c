
#include <stdio.h>
#include <stdlib.h>

int main() {
    int i;
    int *p = malloc(3 * sizeof(int));

    if (p == NULL) return 1;
    for (i = 0; i < 3; i++) p[i] = i + 1;

    int *q = calloc(3, sizeof(int));
    if (q == NULL) {
        free(p);
        return 1;
    }

    int *temp = realloc(p, 5 * sizeof(int));
    if (temp == NULL) {
        free(p);
        free(q);
        return 1;
    }
    p = temp;
    p[3] = 4;
    p[4] = 5;

    printf("malloc/realloc: ");
    for (i = 0; i < 5; i++) printf("%d ", p[i]);

    printf("\ncalloc: ");
    for (i = 0; i < 3; i++) printf("%d ", q[i]);

    free(p);
    free(q);
    printf("\nMemory released successfully.\n");
    return 0;
}
