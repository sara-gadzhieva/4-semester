#include <unistd.h>
#include <stdio.h>
int main() {
	int i;
	if(fork()) {
		sleep(1);
		printf("test");
		_exit(0);
		}
	printf("my pid=%d\n",getpid());
	for(i=0;i<5;i++) {
		printf("my parent is %d\n",getppid());
		sleep(10);
		}
	return 0;
	}
