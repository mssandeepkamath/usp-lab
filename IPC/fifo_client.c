#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
    char *path = "/tmp/fifo";
    char buf[100];
    int fd = open(path, O_RDWR);
    printf("Enter the data to be sent to server\n");
    scanf("%[^\n]s", buf);
    write(fd, buf, sizeof(buf));
    printf("Data sent succesfully\n");
    return 0;
}