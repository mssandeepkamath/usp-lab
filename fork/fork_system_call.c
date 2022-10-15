#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>


/*
  Remember the header files
  Use system(cmd) fot executing command
  fork_val is nothing but child pid when it is greater than 0
  wait(NULL) wil take NULL as a parameter
  Remember getpid() and getppid()
*/


int main()
{
    int fork_val=fork();
    char command[100];
    if(fork_val==0)
    {
        printf("Child process is created\n");
        printf("In child process now\n");
        printf("The process id is: %d\nThe parent process id is: %d\n",getpid(),getppid());
        printf("Enter the command to be executed\n");
        scanf("%s",command);
        system(command);
    }
    else if(fork_val>0)
    {
        wait(NULL);
        printf("In parent process\n");
        printf("The process id is: %d\nThe childs process id is: %d\n",getpid(),fork_val);
    }
    else{
        printf("Error in creating a child process\n");
    }
    return 0;
}