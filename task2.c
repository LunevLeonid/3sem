#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Incorrect usage\n");
        return 1;
    }

    int fd = open(argv[1], O_CREAT|O_WRONLY, S_IWUSR); //argv[1] - name of the file
    if (fd < 0) {
        perror("Failed to open");
        return 3;
    }
    
    ssize_t len = strlen(argv[2]);
    ssize_t i = 0;
    while (i < len) {
        ssize_t count = write(fd, argv[2] + i, len); //argv[2] - text that we write to the file
        if (count < 0) {
            perror("Failed to write\n");
            return 2;
        }
        i += count;
    }
    
    int c = close(fd);
    if (c < 0) {
        perror("Failed to close\n");
        return 2;
    }
    
    return 0;
}
