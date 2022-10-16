#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
	int fd[2], stat;
	pipe(fd);
	if (fork()) {
		char rr[256];
		close(fd[1]);
		wait(&stat);
		read(fd[0], rr, 256);
		printf("%s", rr);
	} else {
		close(fd[0]);
		dup2(fd[1], 1);
		close(fd[1]);
		execl("./202101074_Lab7_1_child.out", "./202101074_Lab7_1_child.out", argv[1], argv[2], NULL);
	}
	return 0;
}