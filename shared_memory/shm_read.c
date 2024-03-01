#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUF_SIZE 32
#define SHM_KEY 0x1234

struct shmseg
{
    int cnt, complete;
    char buf[BUF_SIZE];
};

int main(int argc, char *argv[])
{
    int shmid;
    struct shmseg *shmp;
    shmid = shmget(SHM_KEY, sizeof(struct shmseg), 0644 | IPC_CREAT);
    if (shmid == -1)
    {
        perror("Shared memory");
        return 1;
    }
    shmp = shmat(shmid, NULL, 0);
    if (shmp == (void *)-1)
    {
        perror("Shared memory attach");
        return 1;
    }
    while (shmp->complete != 1)
    {
        printf("segment contains : \n\"%s\"\n", shmp->buf);
        if (shmp->cnt == -1)
        {
            perror("read");
            return 1;
        }
        printf("Reading Process: Shared Memory: Read %d bytes\n",
               shmp->cnt);
        sleep(3);
    }
    printf("Reading Process: Reading Done, Detaching Shared Memory\n");
    if (shmdt(shmp) == -1)
    {
        perror("shmdt");
        return 1;
    }
    printf("Reading Process: Complete\n");
    return 0;
}