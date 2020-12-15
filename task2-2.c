#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define N 512

int main(int argc, char* argv[]) {
	if (argc != 3) {
		printf("Incorrect usage\n");
		return 1;
	}

    int fd = open(argv[1], O_CREAT|O_WRONLY, S_IWUSR); //argv[1] - name of the file
    if (fd < 0) {
    	perror("Failed to open");
    	return 2;
    }
    
    int len = strlen(argv[2]);
    int count = dprintf(fd, "%s\n", argv[2]); //argv[2] - text to write
    if (count < 0) {
    	perror("Failed to write");
    	return 3;
    }
    if (count < len) {
    	printf("Unsuccessful write");
    	return 4;
    }
    
    int c = close(fd);
    if (c < 0) {
    	perror("Failed to close\n");
    	return 5;
    }
    
    return 0;
}
