#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/select.h>
#include <sys/types.h>
#include <fcntl.h>

/*
Remember:
1.Header files 3 sys, 3 std and 1 fcntl
2.Child part is just writing
3.Parent part is select setup+reading value
4.select(fd[0]+1,&fds,NULL,NULL,&tvs)
*/

int main()
{
    int fd[2];
    pipe(fd);
    int fork_val = fork();
    if (fork_val < 0)
    {
        printf("Error in creating child process\n");
        exit(-1);
    }
    else if (fork_val == 0)
    {
        char buf[100];
        printf("CHILD PROCESS\nEnter the data to be sent to the parent\n");
        scanf("%[^\n]s", buf);
        write(fd[1], buf, sizeof(buf));
        printf("Data sent successfully\n");
    }
    else
    {
        char buf[100];
        fd_set fds;
        FD_ZERO(&fds);
        FD_SET(fd[0], &fds);
        struct timeval tvs;
        tvs.tv_sec = 10;
        tvs.tv_usec = 0;
        int select_val = select(fd[0] + 1, &fds, NULL, NULL, &tvs);
        if (select_val == -1)
        {
            printf("Something went wrong in select\n");
            exit(-1);
        }
        else if (select_val)
        {
            printf("PARENT PROCESS\nThe data sent by the child process is:\n");
            read(fd[0], buf, sizeof(buf));
            printf("%s\n", buf);
        }
        else
        {
            printf("No data is sent by child process in 10 seconds\n");
        }
    }
    return 0;
}
