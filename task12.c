#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>

int main(int argc, char* argv[]) {
	printf("Process id: %d\n", getpid());
	printf("Process parent id: %d\n", getppid());
	struct passwd *pwd = getpwuid(getuid());
	if (pwd == NULL) {
		perror("Failed to getpwuid");
		return 1;
	}
	printf("User id: %d\n", pwd->pw_uid);
	printf("User name: %s\n", pwd->pw_name);
	printf("Group id: %d\n", pwd->pw_gid);
	struct group *pgr = getgrgid(pwd->pw_gid);
	if (pgr == NULL) {
		perror("Failed to get group");
		return 1;
	}
	printf("Group name: %s\n", pgr->gr_name);
	return 0;
}

