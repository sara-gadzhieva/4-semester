#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
void *tFunc(void *arg) {
	sleep(200);
	printf("вывод из потока\n");
	return NULL;
	}
int main() {
	pthread_t tchild;
	pthread_create(&tchild,NULL,tFunc,NULL);
	printf("ждем окончания потока\n");
	///pthread_join(tchild,NULL);
	return 0;
	}

