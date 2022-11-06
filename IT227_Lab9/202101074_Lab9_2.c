#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/resource.h>
#include <inttypes.h>

int m=50000,n=10000,t,mat[50000][10000],l;

void* sumit(void *ii){
    int i = *((int*)ii);
    int *sum=(int *)malloc(sizeof(int));
    *sum=0;

    int s = l*i;
    for(int i=0; i<l; i++)     
        for(int j=0;j<n;j++)
            *sum+=mat[i+s][j];

    if(t*l+i<m)               
        for(int j=0;j<n;j++)
            *sum+=mat[t*l+i][j];

    return ((void*)sum);
}

int parallel(){
    pthread_t tid[t];
    int *ret,fs=0,no[t];
    l=m/t;

    for(int i=0; i<t; i++){
        no[i]=i;
        pthread_create(tid+i, NULL, sumit, (void*)(no+i));
    }

    for(int i=0; i<t; i++){
        pthread_join(tid[i], (void**)&ret);
        fs+=(int)(*ret);
    }
    return fs;
}

int serial(){
    int fs=0;
    for(int i=0;i<m;i++)
        for(int j=0;j<n;j++)
            fs+=mat[i][j];
    return fs;
}

uint64_t get_gtod_clock_time ()
{
    struct timeval tv;
    if (gettimeofday (&tv, NULL) == 0)
        return (uint64_t) (tv.tv_sec * 1000000 + tv.tv_usec);
    else
        return 0;
}

int main(){
    int p;
    printf("Enter no. of THREADS : ");    scanf("%d",&t);
    if(t>=m || t<=0)    return 0;
    printf("No. of ROWS are : %d\n",m);
    printf("No. of COLUMS are : %d\n\n",n);

    uint64_t start_time_value, end_time_value, time_diff;
    start_time_value = get_gtod_clock_time();
    p=parallel();
    end_time_value = get_gtod_clock_time();
    time_diff = end_time_value - start_time_value;
    printf("Ans by PARALLEL : %d \n",p);
    printf("Time for PARALLEL : ");
    printf("%"PRIu64"\n\n", time_diff);

    start_time_value = get_gtod_clock_time();
    p=serial();
    end_time_value = get_gtod_clock_time();
    time_diff = end_time_value - start_time_value;
    printf("Ans by SERIAL : %d \n",p);
    printf("Time for SERIAL : ");
    printf("%"PRIu64"\n", time_diff);

    return 0;
}
