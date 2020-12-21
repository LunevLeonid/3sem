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
	if (lstat(argv[1], &st_buf1) == -1) {
		perror("Failed to stat");
		return 2;
	}
	if (!S_ISREG(st_buf1.st_mode)) {
		printf("Not regular read file\n");
		return 3;
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
		close(fd_rd);
		return 5;
	}
	
	if (ftruncate(fd_wr, 0) < 0) {
		perror("Failed to change size of file");
		close(fd_wr);
		close(fd_rd);
		return 3;
	}
	ssize_t i = 0; 
	while (1) {
		ssize_t count_read = pread(fd_rd, buf, N, i);
		if (count_read == -1) {
			perror("Failed to read\n");
			break;
		}
		if (count_read == 0) {
			break;
		}
		
		ssize_t j = 0;
		while (j < count_read) {
			ssize_t count_write = pwrite(fd_wr, buf + j, count_read - j, j + i);
			if (count_write == -1) {
				perror("Failed to write");
				clode(fd_wr);
				close(fd_rd);
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
