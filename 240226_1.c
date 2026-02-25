#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int main() {
	pid_t pid;
	int rv;
	switch(pid=fork()) {
		case -1:
		perror("fork");
		exit(1);
		case 0:
		printf("child: это дочерний процесс\n");
		printf("child: мой pid %d\n",getpid());
		printf("child: pid моего родителя %d\n",getppid());
		printf("child: введите код возврата\n");
		scanf("%d",&rv);
		printf("child: выход\n");
		exit(rv);
		default:
		printf("parent: это родительский процесс\n");
		printf("parent: мой pid %d\n",getpid());
		printf("parent: pid моего ребенка %d\n",pid);
		printf("parent: жду, пока потомок не вызовет exit\n");
		wait(&rv);
		printf("parent: код возврата потомка %d\n",WEXITSTATUS(rv));
		printf("parent: выход\n");
		}
	return 0;
	}
