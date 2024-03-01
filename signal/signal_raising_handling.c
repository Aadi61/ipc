#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
void handler_sigtstp(int signum);
int main() {
void (*sigHandlerReturn)(int);
sigHandlerReturn = signal(SIGTSTP, handler_sigtstp);
if (sigHandlerReturn == SIG_ERR) {
perror("Signal Error: ");
return 1;
}
printf("Testing SIGTSTP\n");
raise(SIGTSTP);
return 0;
}

void handler_sigtstp(int signum) {
if (signum == SIGTSTP) {
printf("Received SIGTSTP\n");
exit(0);
}
else
printf("Received %d Signal\n", signum);
return;
}
