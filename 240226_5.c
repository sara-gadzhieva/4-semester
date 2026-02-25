#include <stdio.h>
#include <unistd.h>
int main() {
	pid_t p;
	while(1) {
		p=fork();
		printf("%d %d\n",getpid(),p);
		}
	return 0;
	}
