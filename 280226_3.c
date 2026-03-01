#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
void f() {
	printf("функция вызвана в новом потоке %d\n",gettid());
	}
void *tFunc(void *arg) {
	sleep(5);
	f();
	printf("вывод из потока %d\n",gettid());
	return NULL;
	}
int main() {
    pthread_t tchild;
    pthread_create(&tchild,NULL,tFunc,NULL);
    printf("ждем окончания потока\n");
    pthread_join(tchild,NULL);
    return 0;	
	}
