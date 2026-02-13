#include <unistd.h>
#include <stdio.h>
int a=10;   
int main() {
    int b=10;
    pid_t p;
    printf("original program, pid=%d, a=%d, b=%d\n", getpid(),a,b);
    p=fork();
    if (p==0) {  
        a++;
        b++;
        printf("in child process, pid=%d, ppid=%d, a=%d, b=%d\n", getpid(),getppid(),a,b);
		} 
    else {       
        a--;
        b--;
        printf("in parent process, pid=%d, fork returned=%d, a=%d, b=%d\n", getpid(),p,a,b);
		}
	}

