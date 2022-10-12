#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>
#include<sys/types.h>

int main(){
    int pid,t,k,i,sig;
    printf("Enter process id to send signal : ");
    scanf("%d",&pid);
    printf("Enter your choice:\n1. to process\n2. to group of processes\n");
    scanf("%d",&t);
    if(t==2)    pid*=-1;
    k=kill(pid,SIGINT);
    return 0;
}
