#include <unistd.h>
#include <stdio.h>
int main() {
	char *arg[]={"/bin/ls",0};
	if(fork()==0) {
		printf("in child process:\n");
		execv(arg[0],arg);
		printf("i will never be called\n");
		}
	sleep(5);
	printf("execution continues in parent process\n");
	return 0;
	}
