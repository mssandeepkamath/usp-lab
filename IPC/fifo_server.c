#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/*
Remember:
1.Set path as /tmp/fifo
2.Server should create fifo using mkfifo with 0666 permission
3.Both should open and read and write (O_RDWR)
4.Do not use while loops
5.Make server run in backgroup to respond
*/

int main()
{
    char *path = "/tmp/fifo";
    char buf[100];
    mkfifo(path, 0666);
    int fd = open(path, O_RDWR);
    printf("Waiting for client to send data\n");
    read(fd, buf, sizeof(buf));
    printf("Data sent by client: %s", buf);
    return 0;
}