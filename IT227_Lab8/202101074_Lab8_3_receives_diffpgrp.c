#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>
#include<sys/types.h>
void handler(){
    printf("Process id %d received SIGINT signal\n", getpid());
}

int main(){
    signal(SIGINT, handler);
    int i,pid,ppid;
    if(fork()){
        printf("Parent PID : %d \n Parent GID : %d\n\n",getpid(),getpgid(0));
    }
    else{
        setpgid(getpid(),0);
        printf("Child PID : %d \n Child GID : %d\n\n",getpid(),getpgid(0));
    }
    pause();
    return 0;
}
