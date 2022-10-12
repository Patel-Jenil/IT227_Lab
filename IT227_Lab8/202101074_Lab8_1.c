#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>

void handler(){
	printf("\nIt took too long to enter the string.\n");
	exit(-1);
}

int main(){
    char s[100];
    printf("Enter a string : ");
    alarm(2);
    signal(SIGALRM,handler);
    scanf("%[^\n]s",s);
    return 0;
}
