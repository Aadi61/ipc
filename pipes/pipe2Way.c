#include<stdio.h>
#include<unistd.h>

int main(){
    int pipefds1[2],pipefds2[2];
    int returnstatus1,returnstatus2,pid;
    char pipe1writemssg[20]="Hi";
    char pipe2writemssg[20]="Hello";
    char readmssg[20];

    returnstatus1=pipe(pipefds1);
    if(returnstatus1 == -1){
        printf("Unable to create pipe 1\n");
        return 1;
    }

    returnstatus2=pipe(pipefds2);
    if(returnstatus2 == -1){
        printf("Unable to create pipe 2\n");
        return 1;
    }

    pid=fork();

    if(pid != 0){
        close(pipefds1[0]);
        close(pipefds2[1]);

        printf("Parent - Writing to pipe 1 - Message 1 is %s\n",pipe1writemssg);
        write(pipefds1[1],pipe1writemssg,sizeof(pipe1writemssg));

        read(pipefds2[0],readmssg,sizeof(readmssg));
        printf("Parent - Reading from pipe 2 - Message 2 is %s\n",readmssg);
    }
    else{
        close(pipefds1[1]);
        close(pipefds2[0]);

        read(pipefds1[0],readmssg,sizeof(readmssg));
        printf("Child - Reading from pipe 1 - Message 1 is %s\n",readmssg);

        printf("Child - Writing to pipe 2 - Message 2 is %s\n",pipe2writemssg);
        write(pipefds2[1],pipe2writemssg,sizeof(pipe2writemssg));
    }
}