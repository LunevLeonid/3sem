#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/vfs.h>

int main(int argc, char* argv[]) {
	struct statfs stfs_buf;
	if (statfs(".", &stfs_buf) == -1) {
		perror("Unable to statfs");
		return 1;
	}
	
	printf("Total space:  %ld B\n", stfs_buf.f_blocks * stfs_buf.f_frsize);
	printf("Free space:  %ld B\n", stfs_buf.f_bfree * stfs_buf.f_frsize);
	printf("Available space:  %ld B\n", stfs_buf.f_bavail * stfs_buf.f_frsize);

	return 0;
}
