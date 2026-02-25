#include <stdio.h>
#include <signal.h>
#include <sys/wait.h>
void sighandler(int sig) {
	printf("in signal handler for signal %d\n",sig);
	int status;
	wait(&status);
	printf("возвращенное значение из потомка %d\n",WEXITSTATUS(status));
	}
int main() {
	signal(SIGCHLD,sighandler);
	if(!fork()) {
		sleep(3);
		_exit(8);
		}
	printf("in parent process\n");
	sleep(120);
	printf("after sleep\n");
	return 0;
	}
