#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#define N 512

int main(int argc, char* argv[]) {
	if (argc != 3) {
		printf("Usage: %s readfile writefile\n", argv[0]);
		return 1;
	}
	
	struct stat st_buf1;
	struct stat st_buf2;
	if (lstat(argv[1], &st_buf1) == -1) {
		perror("Failed to stat");
		return 2;
	}
	if (lstat(argv[2], &st_buf2) == -1) {
		perror("Failed to stat");
		return 2;
	}
	if (S_ISREG(argv[1])) {
		printf("Not regular read file\n");
		return 3;
	}
	if (S_ISREG(argv[2])) {
		printf("Not regular write file\n");
		return 4;
	}
	
	char buf[N];
	int fd_rd = open(argv[1], O_RDONLY);
	if (fd_rd == -1) {
		perror("Failed to open\n");
		return 4;
	}
	
	int fd_wr = open(argv[2], O_WRONLY);
	if (fd_wr == -1) {
		perror("Failed to open\n");
		close(fd_wr);
		return 5;
	}
	
	ssize_t i = 0; 
	while (1) {
		ssize_t count_read = pread(fd_rd, buf, N, i);
		if (count_read == -1) {
			perror("Failed to read\n");
			return 6;
		}
		if (count_read == 0) {
			break;
		}
		
		ssize_t j = 0;
		while (j < count_read) {
			ssize_t count_write = pwrite(fd_wr, buf + j, count_read - j, j + i);
			if (count_write == -1) {
				perror("Failed to write");
				return 7;
			}
			j += count_write;
		}
		
		i += count_read;
	}
	
	if (close(fd_wr) < 0) {
		perror("Failed to close");
	}
	
	if (close(fd_rd) < 0) {
		perror("Failed to close");
	}
	return 0;
}
