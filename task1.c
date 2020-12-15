#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
	if (argc != 2) {
		printf("Not enough arguments");
		return 1;
	}
	
	struct stat st_buf;
	int t = stat(argv[1], &st_buf);
	if (t < 0) {
		perror("Failed to stat");
		return 2;
	}
	
	printf("Mode: %06o\n", st_buf.st_mode);
	printf("Size:  %ld B\n", st_buf.st_size);
	printf("Blocks allocated: %ld\n", st_buf.st_blocks);
	printf("Used space: %ld B\n", st_buf.st_blocks * 512);
	printf("File type: ");
	switch (st_buf.st_mode & S_IFMT) {
		case S_IFBLK: printf("block device\n"); break;
		case S_IFCHR: printf("character device\n"); break;
		case S_IFDIR: printf("directory\n"); break;
		case S_IFIFO: printf("FIFO/pype\n"); break;
		case S_IFLNK: printf("symlink\n"); break;
		case S_IFREG: printf("regular file\n"); break;
		case S_IFSOCK: printf("socket\n"); break;
		default: printf("unknown\n"); break;
	}
	printf("Last status change: %s", ctime(&st_buf.st_ctime));
	return 0;
}
