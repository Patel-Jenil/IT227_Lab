#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<stdint.h>
#include <time.h>
// Jenil_Patel_202101074
// Doubly Linked List using struct
// Declaring global variables here...

int totalPrograms = 0;
typedef struct program Program;

struct program {
    int prog_id;
    char prog_name[50];
    char uid_executing[25];
    uint64_t start_time;
    uint64_t time_elapsed;
    int prog_status; // submitted=1 , running=2, finish=3
    Program *next, *prev;
};
Program *head, *tail;

void programDetails(const Program prog) {
    printf("\n%d: %s", prog.prog_id, prog.prog_name);
}
Program* getDetails() {
    Program* prog = (Program *) malloc(sizeof(Program));
    ++totalPrograms;
    prog->prog_id = totalPrograms;
    printf("Enter Program name: ");
    fgets(prog->prog_name, 50 , stdin);
    printf("Enter uid: ");
    fgets(prog->prog_name, 25 , stdin);
    prog->start_time = time(NULL);
    prog->prog_status = 1;
    return prog;
}

void addProgram() {
    Program* newProg = getDetails();
    if (head == NULL) {
        head = tail = newProg;
    } else {
        tail->next = newProg;
        newProg->prev = tail;
        tail = newProg;
    }
    printf("\nProgram added.\n");
}

void runProgram(int id) {
    if (id <=0 || id > totalPrograms) {
        printf("\nInvalid PID.\n");
        return;
    }
    if ( !head ){
        printf("\nPrograms List is Empty.\n");
    }
    Program* prog = head;
    while ( !prog ) {
        if (prog->prog_id == id) {
            if (id == 2) {
                printf("\nProgram { %s } already running.\n", prog->prog_name);
            } else {
                printf("\nProgram { %s }is now running.\n", prog->prog_name);
            }
            return;
        }
    }
    printf("\nInvalid PID.\n");
}

void completeProgram(int id) {
    if (id <=0 || id > totalPrograms) {
        printf("\nInvalid PID.\n");
        return;
    }
    if ( !head ){
        printf("\nPrograms List is Empty.\n");
    }
    Program* prog = head;
    while ( !prog ) {
        if (prog->prog_id == id) {
            if (id == 3) {
                printf("\nProgram { %s } already completed.\n", prog->prog_name);
            } else {
                printf("\nProgram { %s }is now completed.\n", prog->prog_name);
            }
            return;
        }
    }
    printf("\nInvalid PID.\n");
}

void freeList() {
    Program*temp = head, *nexttemp = head;

    while (nexttemp) {
        nexttemp = temp->next;
        free(temp);
        temp = nexttemp;
    }
    printf("\n***Memory Freed***\n");
}
int main() {

    // __uint64_t current_time = time(NULL);
    // printf("%lu\n",current_time);
    // getchar();
    // __uint64_t next_time = time(NULL);
    // printf ("%lu\n", (next_time - current_time) );
    // Program *head = malloc(sizeof(Program));
    // printf("%d %s\n",head->prog_id, head->prog_name);
    char choice;
    int id;
    while (1) {
        printf("\n==========================================\n");
        printf("1. Add new program.\n");
        printf("2. Run a program.\n");
        printf("3. Complete a program.\n");
        printf("4. Update time-elapsed for all programs.\n");
        printf("5. Remove all completed programs.\n");
        printf("0. Exit.\n");
        scanf("%c", &choice);
        switch(choice) {
        case '1':
            addProgram();
            break;
        case '2':
            printf("Enter I'd of the program: ");
            scanf ("%d",&id);
            // runProgram(id);
            break;
        case '3':
            printf("Enter I'd of the program: ");
            scanf ("%d",&id);
            // completeProgram(id);
            break;
        case '4':
            // updateTimeOfProgram(id);
            break;
        case '5':
            // removeCompletedPrograms();
            break;
        case '0':
            printf("\nAdios Amigo\n\n");
            return 0;
        default:
            printf("Invalid choice!\n");
        } 
    }
    freeList();
    return 0;
}
