#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<signal.h>

void handler_sigint()
{
    printf("The server caught SIGINT\n");
}
void handler_sigfpe()
{
    printf("The server caught SIGFPE\n");
}

void handler_sigsegv()
{
    printf("The server caught SIGSEGV\n");
}

void handler_sigchld()
{
    printf("The server caught SIGCHLD\n");
}

void handler_sigill()
{
    printf("The server caught SIGILL\n");
}



int main()
{

    signal(SIGINT,handler_sigint);
    signal(SIGFPE,handler_sigfpe);
    signal(SIGSEGV, handler_sigsegv);
    signal(SIGCHLD, handler_sigchld);
    signal(SIGILL, handler_sigill);

    while(1);

    return 0;
}