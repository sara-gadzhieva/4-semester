#include <unistd.h>
#include <stdio.h>
int main() {
	for(int i=0;i<3;i++) {
		if(!fork()) _exit(0);
		}
	sleep(120);
	printf("done\n");
	return 0;
	}
