#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#ifdef S_BLKSIZE
#define BLKSIZE S_BLKSIZE
#else
#include <sys/param.h>
#define BLKSIZE DEV_BSIZE
#endif

const char* get_file_type(mode_t f_mode) {
	switch (f_mode & S_IFMT) {
		case S_IFBLK: return "block device";
		case S_IFCHR: return "character device";
		case S_IFDIR: return "directory";
		case S_IFIFO: return "FIFO/pype";
		case S_IFLNK: return "symlink";
		case S_IFREG: return "regular file";
		case S_IFSOCK: return "socket";
		default: return "unknown";
	}
}

int main(int argc, char* argv[]) {
	if (argc != 2) {
		printf("Usage: %s somefile", argv[0]);
		return 1;
	}

	struct stat st_buf;
	if (lstat(argv[1], &st_buf) < 0) {
		perror("Failed to stat");
		return 2;
	}

	printf("Mode: %06o\n", st_buf.st_mode);
	printf("Size:  %ld B\n", st_buf.st_size);
	printf("Blocks allocated: %ld\n", st_buf.st_blocks);
	printf("Used space: %ld B\n", st_buf.st_blocks * BLKSIZE);
	printf("File type: %s\n", get_file_type(st_buf.st_mode));
	printf("All times are in GMT\n");
	printf("Last status change: %s", asctime(gmtime(&st_buf.st_ctime)));
	printf("Last access time : %s", asctime(gmtime(&st_buf.st_atime)));
	printf("Last modification time: %s", asctime(gmtime(&st_buf.st_mtime)));
	return 0;
}
