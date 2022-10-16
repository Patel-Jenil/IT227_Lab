#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>


int i, pid1, pid2, stat,nob=0,fd1[2],fd2[2],stat,qno;
char msg[100];
char* questions[] = {"quit", "You study in which university?","which course are you studying?", "what is your area of interest?"};
char* answers[] = {"quit", "DAIICT", "Systems Programming", "Embedded Systems"};
static void hand2(int);
static void hand1(int);

static void hand1(int ino)
{
    while(1)
    {
        int i;
        nob=read(fd1[0], msg,100 );
        printf("Question in child : %s\n",msg);
        for(i=0;i<4;i++)
        if(!strcmp(msg,questions[i]))
        break;
        if(i==4)
            return;
        write(fd2[1],answers[i],strlen(answers[i])+1);

        if(!i)
            break;
        kill(pid1,SIGUSR2);
    }
    close(fd1[0]);
    close(fd2[1]);
    exit(0);
}

static void hand2(int ino)
{
    while(1)
    {

        nob= read(fd2[0],msg,100);
        printf("Answer in Parent : %s\n",msg);
        if(!qno)
            break;
        printf("Enter the question number: ");
        scanf("%d",&qno);
        if(qno>3 || qno<0)
        {
            write(fd1[1],"Invalid question number",30);
            exit(0);
        }
        write(fd1[1],questions[qno],strlen(questions[qno])+1);
        kill(pid2, SIGUSR1);
    }
    wait(&stat);
    close(fd1[1]);
    close(fd2[0]);
    exit(0);
}


int main()
{
    pipe(fd1);
    pipe(fd2);
    pid1=getpid();
    if( signal( SIGUSR1, hand1) == SIG_ERR  )
    {
        printf("Parent: Unable to create handler for SIGUSR1\n");
    }

    if( signal( SIGUSR2, hand2) == SIG_ERR  )
    {
        printf("Parent: Unable to create handler for SIGUSR2\n");
    }
    if( pid2 = fork())
    {
        close(fd1[0]); // read 
        close(fd2[1]); // write 

            printf("Enter the question number: ");
            scanf("%d",&qno);
            if(qno>3 || qno<0)
            {
                write(fd1[1],"Invalid question number",30);
                return 0;
            }
            write(fd1[1],questions[qno],strlen(questions[qno])+1);
            kill(pid2, SIGUSR1);
            pause();
    }
    else
    {
        close(fd1[1]);
        close(fd2[0]);
        pause();
    }
    return 0;
}
