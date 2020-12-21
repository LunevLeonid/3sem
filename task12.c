#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>


int main(int argc, char* argv[]) {
	printf("Process id: %d\n", getpid());
	printf("Process parent id: %d\n", getppid());
	printf("User id: %d\n", getuid());
	printf("Group id: %d\n", getgid());
	
	int ngroups_max = sysconf(_SC_NGROUPS_MAX);
	gid_t *gr = (gid_t*)calloc(ngroups_max, sizeof(gid_t));
	
	int ngroups = getgroups(ngroups_max, gr);
	printf("Process groups:\n");
	struct group *grg;
	for (int i = 0; i < ngroups; i++) {
		printf("%d", gr[i]);
		grg = getgrgid(gr[i]);
		if (grg == NULL) {
			perror("Failed to getgrgid");
		} else {
			printf("  %s\n", grg->gr_name);
		}
	}
	mode_t mask = umask(S_IWGRP | S_IWOTH);
	printf("Mask: %d\n", mask);
	
	char* dir = get_current_dir_name(); \\not a standart function
	printf("Process current directory: %s\n", dir);
	free(dir);
	
	free(gr);
	return 0;
}
