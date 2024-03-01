#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define FIFO_FILE "/tmp/fifo_twoway"
int main()
{
    int fd, end_process, stringlen, read_bytes;
    char readbuf[80], end_str[5];

    fd = open(FIFO_FILE, O_CREAT | O_RDWR);
    strcpy(end_str, "end");

    while (1)
    {
        printf("Enter string: ");
        fgets(readbuf, sizeof(readbuf), stdin);
        stringlen = strlen(readbuf);
        readbuf[stringlen - 1] = '\0';
        end_process = strcmp(readbuf, end_str);
        // printf("end_process is %d\n", end_process);
        if (end_process != 0)
        {
            write(fd, readbuf, strlen(readbuf));
            printf("FIFOCLIENT: Sent string: \"%s\" and string length"
                   " is %d\n",
                   readbuf, (int)strlen(readbuf));
            read_bytes = read(fd, readbuf, sizeof(readbuf));
            readbuf[read_bytes] = '\0';
            printf("FIFOCLIENT: Received string: \"%s\" and length "
                   "is %d\n",
                   readbuf, (int)strlen(readbuf));
        }
        else
        {
            write(fd, readbuf, strlen(readbuf));
            printf("FIFOCLIENT: Sent string: \"%s\" and string length is "
                   "%d\n",
                   readbuf, (int)strlen(readbuf));
            close(fd);
            break;
        }
    }
}