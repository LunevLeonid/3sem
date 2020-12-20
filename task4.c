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
	if (S_ISREG(st_buf1.st_mode)) {
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
		return 5;
	}
	
	while (1) {
		ssize_t count_read = read(fd_rd, buf, N);
		if (count_read == -1) {
			perror("Failed to read\n");
			close(fd_rd);
			close(fd_wr);
			return 6;
		}
		if (count_read == 0) {
			break;
		}
		
		ssize_t i = 0;
		while (i < count_read) {
			ssize_t count_write = write(fd_wr, buf + i, count_read - i);
			if (count_write == -1) {
				perror("Failed to write");
				return 7;
			}
			i += count_write;
		}
	}
	
	struct timespec om_time[2] = {st_buf1.st_atim, st_buf1.st_mtime};
	
	if (fchmod(fd_wr, st_buf1.st_mode) < 0) {
		perror("Failed to change mode");
		return 8;
	}
	if (futimens(fd_wr, om_time) < 0) {
		perror("Failed to futimens");
		return 9;
	}
	
	if (close(fd_wr) < 0) {
		perror("Failed to close");
	}
	
	if (close(fd_rd) < 0) {
		perror("Failed to close");
	}
	return 0;
}
