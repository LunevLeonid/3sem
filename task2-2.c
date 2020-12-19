#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Usage: %s somefile str\n", argv[0]);
        return 1;
    }

    int fd = open(argv[1], O_CREAT|O_WRONLY, S_IRUSR | S_IWUSR); //argv[1] - name of the file
    if (fd < 0) {
        perror("Failed to open");
        return 2;
    }

    size_t len = strlen(argv[2]);
    int count = dprintf(fd, "%s", argv[2]); //argv[2] - text to write
    if (ftruncate(fd, (long int)len) < 0) {
        perror("Failed to ftruncate");   
    } else if (count < 0) {
        perror("Failed to write");
    } else if (count < len) {
        printf("Unsuccessful write");
    }

    if (close(fd) < 0) {
        perror("Failed to close\n");
        return 5;
    }
    return 0;
}
