#include <unistd.h>
#include <stdio.h>
int main() {
	pid_t p;
	printf ("original program, pid=%d\n",getpid());
	p=fork();
	if(p==0) printf ("in child process, pid=%d, ppid=%d\n",getpid(),getppid());
	else {
		printf ("in parent process, pid=%d, fork returned=%d\n",getpid(),p);
		sleep(10);
		}
	}
