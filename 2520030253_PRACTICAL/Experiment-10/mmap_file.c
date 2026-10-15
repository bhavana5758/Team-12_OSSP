
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>

int main() {
    int fd = open("data.txt", O_RDONLY);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    struct stat st;
    if (fstat(fd, &st) < 0 || st.st_size == 0) {
        printf("File is empty or cannot be checked.\n");
        close(fd);
        return 1;
    }

    char *p = mmap(NULL, st.st_size, PROT_READ,
                   MAP_PRIVATE, fd, 0);

    if (p == MAP_FAILED) {
        perror("mmap");
        close(fd);
        return 1;
    }

    printf("File content: %.*s", (int)st.st_size, p);

    munmap(p, st.st_size);
    close(fd);
    return 0;
}
