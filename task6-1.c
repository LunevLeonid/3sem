#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>

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

const char* get_file_dtype(uint8_t f_type) {
	switch (f_type) {
		case DT_BLK: return "block device";
		case DT_CHR: return "character device";
		case DT_DIR: return "directory";
		case DT_FIFO: return "pipe";
		case DT_LNK: return "symbolic";
		case DT_REG: return "regular file";
		case DT_SOCK: return "UNIX domain socket";
		default: return "unknown???";
	}
}

int main(int argc, char* argv[]) {
	char* buf;
	if (argc > 2) {
		printf("Usage: %s somedirectory", argv[0]);
		return 1;
	} else if (argc == 1) {
		buf = ".";
	} else {
		buf = argv[1];
	}

	DIR* dp = opendir(buf);
	if (dp == NULL) {
		perror("Unable to open directory");
		return 4;
	}

	struct stat st_buf;
	errno = 0;
	struct dirent *dirp;
	while ((dirp = readdir(dp)) != NULL) {
		if (dirp->d_type != DT_UNKNOWN) {
			printf("%-20s", get_file_dtype(dirp->d_type));
		} else {
			if (lstat(dirp->d_name, &st_buf) == -1) {
				printf("unknown???")
			} else {
				printf("%-20s", get_file_type(st_buf.st_mode));
			}
		}
		printf("%s\n", dirp->d_name);
		errno = 0;
	}

	if (errno != 0) {
		perror("Reading directory error");
	}

	if (closedir(dp)) {
		perror("Unable to close");
		return 3;
	}

	return 0;
}
