#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
int main() {
	int fd_in,fd_out;
	char buf[1024];
	memset(buf,0,1024);
	fd_in=open("test.txt",O_RDONLY);
	fd_out=open("test_out.txt",O_WRONLY|O_CREAT,0644);
	fork();
	while(read(fd_in,buf,2)>0) {
		printf("%d: %s\n",getpid(),buf);
		/**sprintf(buf,"%d hello, world\n",getpid());
		write(fd_out,buf,strlen(buf));**/
		sleep(20);
		memset(buf,0,1024);
		}
	return 0;	
	}
