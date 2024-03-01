#include<stdio.h>
#include<unistd.h>

int main(){
    int pipefds[2];
    int returnstatus;
    returnstatus=pipe(pipefds);
    char writeMssg[2][20]={"Hi","Hello"};
    char readMssg[20];
    int pid;

    pid=fork();

    if(pid == 0){
        read(pipefds[0],readMssg,sizeof(readMssg));
        printf("Child - Reading from pipe - Message 1 is %s\n",readMssg);

        read(pipefds[0],readMssg,sizeof(readMssg));
        printf("Child - Reading from pipe - Message 2 is %s\n",readMssg);
    }

    else{
        printf("Parent - Writing to pipe - Message 1 is %s\n",writeMssg[0]);
        write(pipefds[1],writeMssg[0],sizeof(writeMssg[0]));

        printf("Parent - Writing to pipe - Message 2 is %s\n",writeMssg[1]);
        write(pipefds[1],writeMssg[1],sizeof(writeMssg[1]));
    }
}