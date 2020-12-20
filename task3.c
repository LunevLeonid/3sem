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

	struct stat st_buf;
	if (lstat(argv[1], &st_buf) == -1) {
		perror("Failed to stat");
		return 2;
	}
	if (!S_ISREG(st_buf.st_mode)) {
		printf("Not regular read file\n");
		return 3;
	}

	char buf[N];
	int fd_rd = open(argv[1], O_RDONLY); //argv[1] - file that we copy
	if (fd_rd == -1) {
		perror("Failed to open\n");
		return 4;
	}

	int fd_wr = open(argv[2], O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR); //argv[2] - file we copy to
	if (fd_wr == -1) {
		perror("Failed to open\n");
		return 5;
	}

	if (ftruncate(fd_wr, 0) < 0) {
		perror("Failed to change size of file");
		close(fd_wr);
		close(fd_rd);
		return 8;
	}
	while (1) {
		ssize_t count_read = read(fd_rd, buf, N);
		if (count_read == -1) {
			perror("Failed to read");
			break;
		}
		if (count_read == 0) {
			break;
		}
		
		ssize_t i = 0;
		while (i < count_read) {
			ssize_t count_write = write(fd_wr, buf + i, count_read - i);
			if (count_write == -1) {
				perror("Failed to write");
				close(fd_wr);
				close(fd_rd);
				return 7;
			}
			i += count_write;
		}
	}

	if (close(fd_wr) < 0) {
		perror("Failed to close");
	}

	if (close(fd_rd) < 0) {
		perror("Failed to close");
	}
	return 0;
}
