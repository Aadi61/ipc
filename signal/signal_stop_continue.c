#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
void handler_sigtstp(int signum);
int main() {
pid_t pid;
printf("Testing SIGSTOP\n");
pid = getpid();
printf("Open Another Terminal and issue following command\n");
printf("kill -SIGCONT %d or kill -CONT %d or kill -18 %d\n",
pid, pid, pid);
raise(SIGSTOP);
printf("Received signal SIGCONT\n");
return 0;
}