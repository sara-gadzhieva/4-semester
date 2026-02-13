#include <unistd.h>
#include <stdio.h>
int main() {
	pid_t p;
	p=fork();
	printf("fork returned %d\n",p);
	sleep(30);
	}
