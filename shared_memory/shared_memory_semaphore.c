#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

int main()
{
    extern int errno;
    // Note the testfile.txt should exist (In this case it should be present in working directory)
    // If you get output as waiting for semaphore.., try changing the second param of ftok (example: 65 -> 90).
    key_t key = ftok("./testfile.txt", 65);
    int shmid = shmget(key, 4096, IPC_CREAT | 0666);   // body: shmget(key, sizeOfMemorySegment, flag )
    char *shmstr = (char *)shmat(shmid, (void *)0, 0); // body: shmat(shmid, address(keep it 0 so that compiler decides),flag)
    int semid = semget(key, 1, IPC_CREAT | 0666);      // body: semget(key, nsem , flag)
    int x = semctl(semid, 0, GETVAL);                  // body: semctl(semid,semnum, cmd)
    int has_waited = 0;
    if (x == -1)
    {
        printf("Some unexpected error occured\n");
        return 0;
    }
    printf("Waiting for shared memory to be available...\n");
    while (semctl(semid, 0, GETVAL) != 0)
        has_waited = 1;

    if (has_waited == 1)
    {
        printf("The data written by other Process in Shared memory is: %s\n", shmstr);
        exit(-1);
    }
    semctl(semid, 0, SETVAL, 1);
    printf("Shared memory is now available...\nSemaphore with semid %d is now locked by Process %d\nEnter data to be entered in the shared memory\n", semid, getpid());
    scanf("%[^\n]s", shmstr);
    printf("Semaphore is now sleeping...\n");
    sleep(5);
    printf("The data in the shared memory is: %s\nSemaphore has been in unlocked\nProcess %d exiting...\n", shmstr, getpid());
    semctl(semid, 0, SETVAL, 0);
    shmdt(shmstr);                 // dettach the memory segment
    shmctl(shmid, IPC_RMID, NULL); // destroy shm
    printf("Shared memory is detached and destroyed..\n");
}
