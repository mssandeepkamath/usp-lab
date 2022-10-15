#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

/*
Remember:
1.CLIENT will wait infinite fot message creation hence use IPC_CREAT|0666
2.Note  msgrcv is == -1 inside while
3.Make a garbage character after server response input
4.msgsnd will have 4 parameter ie. msgid,msgbuf,sizeof(msgbuf->mtext),IPC_NOWAIT
5.msgrcv have 1 extra ie. the mtype
6.Before sending anydata make sure you have mtype set
7.msgctl take msgid,IPC_RMID and NULL has parameters
8.Nor server nor client is daemon and thus run it normally
9.Destroy the message queue in client side
*/

struct message
{
    long mtype;
    char mtext[100];
};

int main()
{
    struct message* msgbuf=(struct message*)malloc(sizeof(struct message));
    key_t key=1;
    int msgid;
    msgid=msgget(key,IPC_CREAT|0666);
    printf("SERVER\n");
    printf("Waiting for request from CLIENT\n");
    while(msgrcv(msgid,msgbuf,sizeof(msgbuf->mtext),1,IPC_NOWAIT)==-1);
    printf("The request from CLIENT is: %s\n",msgbuf->mtext);
    printf("Enter the SERVER response\n");
    msgbuf->mtype = 3;
    scanf("%[^\n]s",msgbuf->mtext);
    char garb;
    scanf("%c",&garb);
    msgsnd(msgid,msgbuf,sizeof(msgbuf->mtext),IPC_NOWAIT);
    printf("Response sent successfully\n");
    printf("Message queue destroyed..\n");
    return 0;
}