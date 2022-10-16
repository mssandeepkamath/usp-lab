#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>
#include<signal.h>
#include<pwd.h>
#include<shadow.h>
#include<crypt.h>
#include<syslog.h>
#include<fcntl.h>

/*
Remember:
1.Run gcc daemon.c -lcrypt
2.Header file <pwd> <crypt> <shadow> <syslog> 
3.Functions and structures. getpwnam, getspnam and more
4.Creating daemon process
5.Closing file descriptors
6.In client while accepting password give a space
7.Learn delimiter part
*/

static void daemon_skeleton()
{
    pid_t pid;
    pid=fork();

    if(pid<0)
    exit(EXIT_FAILURE);
    if(pid>0)
    exit(EXIT_SUCCESS);

    if(setsid() < 0)
    exit(EXIT_FAILURE);

    signal(SIGCHLD,SIG_IGN);
    signal(SIGHUP,SIG_IGN);

    pid=fork();
    if (pid < 0)
        exit(EXIT_FAILURE);
    if (pid > 0)
        exit(EXIT_SUCCESS);
    
    umask(0);

    chdir("/");

    int fd=0;
    for(fd=sysconf(_SC_OPEN_MAX);fd>0;fd--)
    {
        close(fd);
    }

    openlog("firstdaemon",LOG_PID,LOG_DAEMON);
}

int checkPassword(const char *user,const char *password)
{
    struct passwd *passwdEntry=getpwnam(user);
    if(!passwdEntry)
    {
        printf("User doesnot exist\n");
        return 1;
    }

    struct spwd *shadowEntry=getspnam(user);
    if(!shadowEntry)
    {
        printf("Failed to read shadow entry of the user\n");
        return 1;
    }

    return strcmp(shadowEntry->sp_pwdp,crypt(password,shadowEntry->sp_pwdp));

}

int main()
{
    daemon_skeleton();
    while(1)
    {
        syslog(LOG_NOTICE,"Daemon started...");
        const char *path1="/tmp/fifo_read";
        const char *path2="/tmp/fifo_write";
        mkfifo(path1,0666);
        mkfifo(path2,0666);
        char pass_name_buf[100];
        int fd1=open(path1,O_RDONLY);
        read(fd1,pass_name_buf,sizeof(pass_name_buf));
        close(fd1);
        char delimiter[]=" ";
        char *ptr=strtok(pass_name_buf,delimiter);
        char *name=malloc(sizeof(char)*100);
        char *password=malloc(sizeof(char)*100);
        name=ptr;
        ptr=strtok(NULL,delimiter);
        password=ptr;

        int fd2=open(path2,O_WRONLY);
        int compare_result=checkPassword(name,password);
        if(compare_result==0)
        {
            write(fd1, "Access permitted", sizeof("Access permitted"));
            break;
        }
        else{
            write(fd1, "Access denied", sizeof("Access permitted"));
            break;
        }
        sleep(2000);
        close(fd2);
    }
    syslog(LOG_NOTICE,"Daemon terminated...");
    closelog();

    return 0;
}