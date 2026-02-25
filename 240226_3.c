#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
int main() {
	int status;
	for(int i=0;i<3;i++) if(!fork()) {
		_exit(0);
		}
	wait(NULL);
	sleep(120);
	printf("done\n");
	return 0;
	}
