#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>

int main()
{
    const char *path1 = "/tmp/fifo_read";
    const char *path2 = "/tmp/fifo_write";
    char name[100],password[100],response[100];
    password[0]=' ';
    printf("Enter the username and password one by one\n");
    scanf("%s",name);
    scanf("%s",password+1);
    strcat(name,password);


    int fd1=open(path1,O_WRONLY);
    write(fd1,name,sizeof(name));
    close(fd1);

    int fd2=open(path2,O_RDONLY);
    read(fd2,response,sizeof(response));
    close(fd2);

    if (strcmp(response, "Access permitted")==0)
    {
        printf("Access permitted\n");
        printf("Accessing the file...\nFile content:\n");
        char content[1000];
        char *path="./pipe.c";
        int fd=open(path,O_RDONLY);
        read(fd,content,sizeof(content));
        close(fd);
        printf("%s",content);
    }
    else{
        printf("Access Denied\n");
    }
    
    return 0;
}