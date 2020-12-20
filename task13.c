#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <sys/wait.h>

void print_process_info(const char* name) {
	printf(%s\nprocess id %d\nparent process id %d\nuser id %d\group id, name, getpid(), getppid(), getuid(), getgid());
	return;
}

int main() {
	pid_t child_id = fork();
	switch (child_id) {
	case -1:
		perror("Failed to make a new process");
		return 1;
	case 0:
		print_process_info("child");
		break;
	default:
		wait(0);
		print_process_info("parent");
		break;
	}
	return 0;
}
