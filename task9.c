#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/vfs.h>

int main(int argc, char* argv[]) {
	if (argc != 2) {
		printf("Usage: %s somefile\n", argv[0]);
		return 1;
	}

	struct statvfs stfs_buf;
	if (statvfs(argv[1], &stfs_buf) == -1) {
		perror("Failed to statvfs");
		return 1;
	}

	printf("Total space:  %ld B\n", stfs_buf.f_blocks * stfs_buf.f_frsize);
	printf("Free space:  %ld B\n", stfs_buf.f_bfree * stfs_buf.f_frsize);
	printf("Available space:  %ld B\n", stfs_buf.f_bavail * stfs_buf.f_frsize);

	return 0;
}
