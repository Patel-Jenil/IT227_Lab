#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int f1[2], f2[2];
    char *questions[] = {"Quit", "You study in which university?", "which course are you studying?", "what is your area of interest?"};
    char *answers[] = {"Quit", "DAIICT", "Computer Systems Programming", "Embedded Systems"};
    pipe(f1);
    pipe(f2);
    if (fork()) {
        close(f1[0]);
        close(f2[1]);
        int stat;
        while (1) {
            int n;
            char msg[256];
            printf("Enter the question no. : "); // asking quetion no.
            scanf("%d", &n);
            if (n > 3 || n < 0) { // invalid condition checking
                write(f1[1], "Invalid question number", 24);
                return 0;
            }
            write(f1[1], questions[n], strlen(questions[n]) + 1); // sending quetion to child
            int nob = read(f2[0], msg, 256);                      // recieving answer from child
            printf("answer in parent : %s\n", msg);
            if (!n)
                break; // quit condition
        }
        wait(&stat);
        close(f1[1]);
        close(f2[0]);
    } else {
        close(f1[1]);
        close(f2[0]);
        while (1) {
            char msg[256];
            int i, nob = read(f1[0], msg, 256); // recieving question from parent
            printf("question in child : %s\n", msg);
            for (i = 0; i < 4; i++) // finding quetion index
                if (!strcmp(msg, questions[i]))
                    break;
            if (i == 4)
                return 0;                                     // invalid quetion case
            write(f2[1], answers[i], strlen(answers[i]) + 1); // sending answer to parent
            if (!i)
                break; // quit condition
        }
        close(f1[0]);
        close(f2[1]);
    }
    return 0;
}