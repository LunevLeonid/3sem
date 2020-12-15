#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>

int main(int argc, char* argv[]) {
	if (argc > 2) {
		printf("Too much arguments");
		return 1;
	}
	if (argc == 1) {
		argv[1] = ".";
	}
	
	DIR* dp = opendir(argv[1]);
	if (dp == NULL) {
		perror("Unable to open directory");
		return 4;
	}
	
	struct stat st_buf;
	errno = 0;
	struct dirent *dirp = readdir(dp);
	if (errno != 0) {
		perror("Failed to read directory");
		return 5;
	}
	while (dirp != NULL) {
		if (dirp->d_type != DT_UNKNOWN) {
			switch(dirp->d_type) {
			case DT_BLK: printf("block device            "); break;
			case DT_CHR: printf("character device        "); break;
			case DT_DIR: printf("directory               "); break;
			case DT_FIFO: printf("pipe                    "); break;
			case DT_LNK: printf("symbolic link           "); break;
			case DT_REG: printf("regular file            "); break;
			case DT_SOCK: printf("UNIX domain socket      "); break;
			}
		} else {
			if (lstat(dirp->d_name, &st_buf) == -1) {
				perror("Unable to stat");
				return 2;
			}
			switch (st_buf.st_mode & S_IFMT) {
			case S_IFBLK:  printf("block device          "); break;
			case S_IFCHR:  printf("character device      "); break;
			case S_IFDIR:  printf("directory             "); break;
			case S_IFIFO:  printf("FIFO/pipe             "); break;
			case S_IFLNK:  printf("symlink               "); break;
			case S_IFREG:  printf("regular file          "); break;
			case S_IFSOCK: printf("socket                "); break;
			default:       printf("unknown?              "); break;
			}
		}
		printf("%s\n", dirp->d_name);
		errno = 0;
		dirp = readdir(dp);
		if (errno != 0) {
			perror("Failed to read");
			return 6;
		}
	}
	
	if (closedir(dp)) {
		perror("Unable to close");
		return 3;
	}
	
	return 0;
}
