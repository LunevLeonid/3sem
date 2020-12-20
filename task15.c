#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

int last_signal;

void listener(int sig) {
	last_signal = sig;
}

int main() {
	if (signal(SIGTERM, listener) == SIG_ERR) {
		perror("Failed to read signal");
		return 1;
	}
	if (signal(SIGINT, listener) == SIG_ERR) {
		perror("Failed to read signal");
		return 2;
	}
	if (signal(SIGQUIT, listener) == SIG_ERR) {
		perror("Failed to read signal");
		return 3;
	}

	while(1) {
		printf("1\n");
		pause();
		switch (last_signal) {
			case SIGTERM:
				printf("Can't stop process, try something else\n");
				break;
			case SIGINT:
				printf("Can't stop process, try something else\n");
				break;
			case SIGQUIT:
				printf("Can't stop process, try something else\n");
				break;
			default:
				printf("unknown signal");
				break;
		}
	}
	return 0;
}
