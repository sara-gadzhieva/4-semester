#include <stdio.h>
#include <pthread.h>
void *tFunc(void *arg) {
	static int ret=17;
	printf("hello from tread\n");
	return &ret;
	}
int main() {
	pthread_t tchild;
	void *status;
	pthread_create(&tchild,NULL,tFunc,NULL);
	pthread_join(tchild,&status);
	printf("%d\n",*(int *)status);
	}
