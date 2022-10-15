#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<string.h>

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
    printf("Waiting for message queue..\n");
    msgid=msgget(key,IPC_CREAT|0666);
    while(msgid==-1)
    {
        msgid = msgget(key, IPC_CREAT | 0666);
    }
    printf("Message queue established..\n");
    printf("CLIENT\n");
    printf("Request to be sent to SERVER is: Page Refresh\n");
    strcpy(msgbuf->mtext,"Page Refresh");
    msgbuf->mtype=1;
    msgsnd(msgid,msgbuf,sizeof(msgbuf->mtext),IPC_NOWAIT);
    printf("Request sent successfully..\n");
    printf("Waiting for response from SERVER\n");
    while (msgrcv(msgid, msgbuf, sizeof(msgbuf->mtext), 3, IPC_NOWAIT) == -1);
    printf("The response from the SERVER is %s\n",msgbuf->mtext);
    printf("CLIENT disconnected\n");
    msgctl(msgid, IPC_RMID, NULL);
    return 0;
}