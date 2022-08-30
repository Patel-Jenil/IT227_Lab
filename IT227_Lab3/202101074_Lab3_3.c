#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
// Jenil_Patel_202101074
// Doubly Linked List using struct
// Declaring global variables here...
int totalPrograms = 0;
typedef struct program Program;

// Function Declarations
void programDetails(const Program*);
void showPrograms();
Program* getDetails();
void addProgram();
void runProgram(int );
void completeProgram(int );
Program* deleteProgram(Program* );
void freeList();
void updateElapsesTime();
void removeAllCompletedPrograms();

struct program {
    int prog_id;
    char prog_name[50];
    char uid_executing[25];
    uint64_t start_time;
    uint64_t time_elapsed;
    int prog_status; // submitted=1 , running=2, finish=3
    Program *next, *prev;
};
Program *head = NULL, *tail = NULL;

void programDetails(const Program* prog) {
    if (!prog)
        return;
    printf("\n* Program-ID:%d\t\tProgram name:%s\n", prog->prog_id, prog->prog_name);
    printf("  User-ID:%s\t\tStatus: ", prog->uid_executing);
    if (prog->prog_status == 1) {
        printf("Submitted.\n");
    } else if (prog->prog_status == 2) {
        printf("Running.\n");
    } else {        
        printf("Completed.\n");
    }
    printf("  Start-Time: %s",ctime(&(prog->start_time)));
    printf("  Elapsed-Time: ");
    if (prog->time_elapsed > 59) {
        printf("%lu min %lu sec\n", (unsigned int)prog->time_elapsed/60 , (unsigned) prog->time_elapsed%60 );
    } else {
        printf("%lu sec\n", prog->time_elapsed);
    }
}

void showPrograms() {
    Program* prog = head;
    if (head == NULL) {
        printf("\nNo Programs at the moment.\n");
        return;
    }
    printf("\nProgram List:\n");
    updateElapsesTime();
    while (prog) {
        programDetails(prog);
        prog = prog->next;
    }
}

Program* getDetails() {
    Program* prog = (Program *) malloc(sizeof(Program));
    prog->next = NULL;
    prog->prev = NULL;
    ++totalPrograms;
    prog->prog_id = totalPrograms;
    printf("Enter Program name: ");
    fgets(prog->prog_name, 50 , stdin);
    prog->prog_name[strcspn(prog->prog_name,"\n")] = '\0';
    printf("Enter User-ID: ");
    fgets(prog->uid_executing, 25 , stdin);
    prog->uid_executing[strcspn(prog->uid_executing,"\n")] = '\0';
    prog->start_time = time(NULL);
    prog->time_elapsed = 0;
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
    while ( prog ) {
        if (prog->prog_id == id) {
            if (prog->prog_status == 2) {
                printf("\nProgram { %s } is already running.\n", prog->prog_name);
            } else {
                prog->prog_status=2;
                prog->start_time = time(NULL);
                printf("\nProgram { %s } is now running.\n", prog->prog_name);
            }
            return;
        }
        prog=prog->next;
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
    while ( prog ) {
        if (prog->prog_id == id) {
            if (prog->prog_status == 3) {
                printf("\nProgram { %s } is already completed.\n", prog->prog_name);
            } else {
                prog->prog_status=3;
                printf("\nProgram { %s } is now completed.\n", prog->prog_name);
            }
            return;
        }
        prog = prog->next;
    }
    printf("\nInvalid PID.\n");
}

Program * deleteProgram(Program* prog) {
    if (prog == NULL)
        return NULL;
    Program *temp = prog, *temp2=prog->next;
    int curr_id = prog->prog_id;
    while(temp2) {
        temp2->prog_id = curr_id++;
        temp2 = temp2->next;
    }
    --totalPrograms;
    if (prog == head) {
        if (head == tail) {
            head = tail = NULL;
            free(temp);
            return NULL;
        } else {
            head = head->next;
            head->prev = NULL;
            free(temp);
            return head;
        }
    } else {
        if (temp == tail) {
            tail = temp->prev;
            tail->next = NULL;
            free(temp);
            return tail;
        } else {
            Program * temp3 = temp->next;
            (temp->prev)->next = temp->next;
            (temp->next)->prev = temp->prev;
            free(temp);
            return temp3;
        }
    }
}

void updateElapsesTime() {
    Program* prog = head;
    if (prog == NULL)
        return;
    uint64_t current_time = time(NULL);
    while (prog) {
        if (prog->prog_status == 2) {
            prog->time_elapsed = current_time - prog->start_time;
        }
        prog = prog->next;
    } 
}

void removeAllCompletedPrograms() {
    if (head == NULL) {
        printf("\nNo Programs at the moment.\n");
        return;
    }
    Program* temp = head;
    int isIT = 0;
    while (temp) {
        if (temp->prog_status == 3) {
            temp = deleteProgram(temp);
            isIT++;
        } else {
            temp = temp->next;
        }
    }
    if (isIT) {
        printf("\n%d completed program%sremoved.\n", isIT, isIT==1?" ":"s ");
    } else {
        printf("\nNo completed Programs at the moment.\n");
    }
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

    char choice;
    int id;
    while (1) {
        printf("\n==========================================\n");
        showPrograms();
        printf("\n==========================================\n");
        printf("\n1. Add new program.\n");
        printf("2. Run a program.\n");
        printf("3. Complete a program.\n");
        printf("4. Update time-elapsed for running programs.\n");
        printf("5. Remove all completed programs.\n");
        printf("0. Exit.\n");
        printf("Choice: ");
        scanf("%c", &choice);
        switch(choice) {
        case '1':
            getchar();
            addProgram();
            break;
        case '2':
            printf("Enter I'd of the program: ");
            scanf ("%d",&id);
            runProgram(id);
            getchar();
            break;
        case '3':
            printf("Enter I'd of the program: ");
            scanf ("%d",&id);
            completeProgram(id);
            getchar();
            break;
        case '4':
            if (head==NULL){
                printf("\nNo Programs at the moment.\n");
            } else {
                printf("\n***Updated Elapsed Time for Running Programs***\n");
                updateElapsesTime();
            }
            getchar();
            break;
        case '5':
            removeAllCompletedPrograms();
            getchar();
            break;
        case '0':
            printf("\nAdios Amigo\n");
            freeList();
            getchar();
            getchar();
            return 0;
        default:
            printf("Invalid choice!\n");
            getchar();

        }
        getchar();
    }
    return 0;
}