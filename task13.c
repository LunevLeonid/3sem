#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <sys/wait.h>

void print_process_info() {
	printf("Process id: %d\n", getpid());
	printf("Process parent id: %d\n", getppid());
	struct passwd *pwd = getpwuid(getuid());
	if (pwd == NULL) {
		perror("Failed to getpwuid");
	} else {
		printf("User id: %d\n", pwd->pw_uid);
		printf("Group id: %d\n", pwd->pw_gid);
		struct group *gr = getgrgid(pwd->pw_gid);
		if (pwd == NULL) {
			perror("Failed to getpwuid");
		} else {
		printf("Group name: %s\n", gr->gr_name);
	}
}
return;
}

int main() {
	pid_t child_id = fork();
	switch (child_id) {
	case -1:
		perror("Failed to make a new process");
		return 1;
	case 0:
		printf("Child process:\n");
		print_process_info();
		break;
	default:
		wait(0);
		printf("Parent process:\n");
		print_process_info();
		break;
	}
	return 0;
}
