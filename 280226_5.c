#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
void *tFunc(void *arg) {
	int *a=(int *)malloc(10*sizeof(int));
	for(int i=0;i<10;i++) a[i]=i*2;
	printf("hello from tread\n");
	return a;
	}
int main() {
	pthread_t tchild;
	void *status;
	pthread_create(&tchild,NULL,tFunc,NULL);
	pthread_join(tchild,&status);	
	int *p=status;
	for(int i=0;i<10;i++) printf("%d\n",p[i]);
	return 0;
	}
