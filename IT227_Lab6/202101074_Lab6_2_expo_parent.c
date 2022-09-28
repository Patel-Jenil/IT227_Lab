#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    if (argc < 3 && (argc % 2 == 1)) {
        printf("USAGE: parent_process.out <num1> <num2> ...\n");
        exit(1);
    }
    int childPID, status;

    for (int i = 0; i < argc - 1; i += 2) {

        if (fork() == 0) /* Child */ {
            printf("Given x for finding e^x is %s and n is %s \n", argv[i+1], argv[i+2]);
            execl("./202101074_Lab6_1_expo_child.out", "./202101074_Lab6_1_expo_child.out", argv[i + 1], argv[i + 2], NULL); /* Execute other program */
            fprintf(stderr, "Could not execute %s \n", argv[1]);
        } else {
            childPID = wait(&status);
            printf("Parent %d : done\n", getpid());
            printf("Child with PID= %d finished\n", childPID);

            if WIFEXITED (status) {
                printf("Child with PID %d terminated normally\n", childPID);
                printf("Child with PID %d exited with exit code %d\n", childPID, WEXITSTATUS(status));
            } else if WIFSIGNALED (status) {
                printf("Child with PID %d was terminated by signal %d\n", childPID, WTERMSIG(status));
            } else {
                printf("Child with PID %d had abnormal termination\n", childPID);
            }
        }
    }
    return 0;
}