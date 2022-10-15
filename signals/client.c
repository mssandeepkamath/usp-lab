#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>

/*
Remember:
1.Header file <signal.h>
2.While(1) in both client and server side
3.Kill(server_id,SIGNAL_ID)
4.signal(SIGNAL_ID,handler_name_only)
5.Get server_id by using ps command in server terminal
*/


int main()
{
    int opt,server_id;
    printf("Enter the server-id\n");
    scanf("%d",&server_id);
    while(1)
    {
        printf("Enter the option\nGenerate Signal:\n1.SIGINT\n2.SIGFPE\n3.SIGSEGV\n4.SIGCHLD\n5.SIGILL\n6.Exit\n");
        scanf("%d",&opt);
        switch(opt)
        {
            case 1:
            {
                kill(server_id,SIGINT);
                break;
            }
            case 2:
            {
                kill(server_id, SIGFPE);
                break;
            }
            case 3:
            {
                kill(server_id, SIGSEGV);
                break;
            }
            case 4:
            {
                kill(server_id, SIGCHLD);
                break;
            }
            case 5:
            {
                kill(server_id, SIGILL);
                break;
            }
            default: exit(0);
        }
    }
   
    return 0;
}