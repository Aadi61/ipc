
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
int main() {
int mypid, myppid;
printf("Program to know PID and PPID's information\n");
mypid = getpid(); // return process-id
myppid = getppid(); // return parents process-id
printf("My process ID is %d\n", mypid);
printf("My parent process ID is %d\n", myppid);
printf("Cross verification of pid's by executing"
"process commands on shell\n");
system("ps -ef");
return 0;
}
