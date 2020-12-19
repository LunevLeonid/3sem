#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define N 512

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Usage: %s somefile str\n", argv[0]);
        return 1;
    }

    int fd = open(argv[1], O_CREAT|O_WRONLY, S_IRUSR | S_IWUSR); //argv[1] - name of the file
    if (fd == -1) {
        perror("Failed to open");
        return 3;
    }

    size_t len = strlen(argv[2]);
    if (ftruncate(fd, (long int)len) < 0) {
        perror("Failed to change length of the file");
    } else {
        ssize_t i = 0;
        while (i < (ssize_t)len) {
            ssize_t count = write(fd, argv[2] + i, len - i); //argv[2] - text that we write to the file
            if (count < 0) {
                perror("Failed to write\n");
                break;
            }
            i += count;
        }
    }

    if (close(fd) < 0) {
        perror("Failed to close\n");
        return 2;
    }

    return 0;
}
