
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

int main() {
    char buffer[1024];
    ssize_t n;
    int in, out;
    clock_t start, end;

    FILE *fp = fopen("input.txt", "w");
    if (fp == NULL) return 1;
    fputs("Hello! This is a file copy experiment.\n", fp);
    fclose(fp);

    start = clock();
    in = open("input.txt", O_RDONLY);
    out = open("copy_sys.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (in < 0 || out < 0) return 1;

    while ((n = read(in, buffer, sizeof(buffer))) > 0)
        write(out, buffer, n);

    close(in);
    close(out);
    end = clock();
    printf("System call copy time: %f seconds\n",
           (double)(end - start) / CLOCKS_PER_SEC);

    start = clock();
    FILE *src = fopen("input.txt", "r");
    FILE *dest = fopen("copy_stdio.txt", "w");
    if (src == NULL || dest == NULL) return 1;

    while ((n = fread(buffer, 1, sizeof(buffer), src)) > 0)
        fwrite(buffer, 1, n, dest);

    fclose(src);
    fclose(dest);
    end = clock();
    printf("Standard I/O copy time: %f seconds\n",
           (double)(end - start) / CLOCKS_PER_SEC);

    return 0;
}
