#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
void *tFunc(void *arg) {
	printf("вывод из потока, значение переменной а=%d\n",*(int *)arg);
	return NULL;
	}
int main() {
	pthread_t tchild;
	int a=10;
	pthread_create(&tchild,NULL,tFunc,&a);
	pthread_join(tchild,NULL);
	return 0;
	}
