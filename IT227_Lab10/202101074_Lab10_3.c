#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <math.h>
#include <semaphore.h>

sem_t semaphore;
int ptable[5][3];
int entry=0;
int rerandomCheck(int processID) {
    for(int i=0;i<entry;i++) {
        if(ptable[entry][0] == processID) {
            processID = rand()%10;
            return processID;
        }
    }
    return processID;
}

void *pTableWriteRW(void *str) {
	int process_id = rand() % 10;
    int page_number = (rand() % 1000) + 50;
    int frequency = 1;

	sem_wait(&semaphore);
    if(entry < 5) {
        process_id = rerandomCheck(process_id);
        ptable[entry][0] = process_id;
        ptable[entry][1] = page_number;
        ptable[entry][2] = frequency;
        entry++;
    } else {
        int minFreqVal=ptable[0][2];
        int minFreqPos=0;
        for(int i=1;i<5;i++) {
            if(ptable[i][2] < minFreqVal) {
                minFreqVal = ptable[i][2];
                minFreqPos = i;
            }
        }
        process_id = rerandomCheck(process_id);
        ptable[minFreqPos][0] = process_id;
        ptable[minFreqPos][1] = page_number;
        ptable[minFreqPos][2] = frequency;

    }
	sem_post(&semaphore);
}

void *pTableReadRW(void *str) {
	int process_id = rand() % 10;
	sem_wait(&semaphore);
	for(int i=0;i<5;i++) {
        if(ptable[i][0] == process_id)
            ptable[i][2]++;
    }
	sem_post(&semaphore);
}

int main() {
    sem_init(&semaphore, 0, 20);
	pthread_t threads[20];

    for(int i=0;i<20;i++) {
        if(i%2==0)
            pthread_create(&threads[i], NULL, pTableWriteRW, NULL);
        else
            pthread_create(&threads[i], NULL, pTableReadRW, NULL);
    }

	for(int i=0;i<20;i++) {
        pthread_join(threads[i], NULL);
    }

    printf("processID  page_number  frequency\n");
    for(int i=0;i<5;i++) {
        printf("%d %d %d\n",ptable[i][0],ptable[i][1],ptable[i][2]);
    }

	exit(0);
}