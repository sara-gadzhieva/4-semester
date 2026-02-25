#include <stdio.h>
#include <string.h>
#include <unistd.h>
int main(int argc,char* argv[]) {
	int pipedes[2];
	pid_t pid;
	pipe(pipedes);
	pid=fork();
	if(pid>0) {
		char *str="string passed via pipe\n";
		close(pipedes[0]);
		write(pipedes[1],str,strlen(str)+1);
		close(pipedes[1]);
		}
	else {
		char buf[1024];
		int len;
		///while((len=read(pipedes[0],buf,2))!=0)
		len=read(pipedes[0],buf,1024);
		write(1,buf,len);
		close(pipedes[0]);
		}
	return 0;
	}
