
#include <stdio.h>
#include <stdlib.h>

int global_var = 10;
static int static_var = 20;

void display() {
    printf("Code address:   %p\n", (void *)display);
}

int main() {
    int local_var = 30;
    int *heap_var = malloc(sizeof(int));

    if (heap_var == NULL) {
        perror("malloc");
        return 1;
    }

    *heap_var = 40;

    display();
    printf("Global address: %p\n", (void *)&global_var);
    printf("Static address: %p\n", (void *)&static_var);
    printf("Heap address:   %p\n", (void *)heap_var);
    printf("Stack address:  %p\n", (void *)&local_var);

    free(heap_var);
    return 0;
}
