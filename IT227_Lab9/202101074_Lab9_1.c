#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <unistd.h>
double sroot[100];
void* root(void *ii){
    int i = *((int*)ii) * 10;
    for(int j=0;j<10;j++){
        sroot[i+j]=sqrt(i+j);
    }
}

int main(){
    pthread_t tid[10], no[10];
    int *ret;
    for(int i=0; i<10; i++)
        no[i]=i;
        
    for(int i=0; i<10; i++){
        pthread_create(tid+i, NULL, root, (void*)(no+i));
    }
    printf("\nPlease Wait...\n");
    for(int i=0; i<10; i++){
        pthread_join(tid[i], (void**)&ret);
    }
    for(int i=0;i<100;i++){
        if(!(i%10))
            printf("\n");
        
        printf("%lf ",sroot[i]);
    }
    printf("\n");
    return 0;
}