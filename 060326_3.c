#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <semaphore.h>
#include <stdbool.h>
char line[256];
bool finished=false;
sem_t input_ready;
sem_t invert_ready;
void* run_input(void*) {
	int l;
	while(true) {
		sem_wait(&invert_ready);
		printf("поток 1: введи строку: \n");
		fgets(line,255,stdin);
		l=strlen(line);
		if(l>0 && line[l-1]=='\n') {
			line[l-1]=0; --l;
			}
		if(l>0 && line[l-1]=='\r') {
			line[l-1]=0; --l;
			}
		if(l==0) finished=true;
		sem_post(&input_ready);
		if(finished) break;		
		}
	printf("первый поток заканчивает работу\n");
	return NULL;
	}
void* run_invert(void*) {
	int i,l;
	while(true) {
		sem_wait(&input_ready);
		if(finished) break;
		l=strlen(line);
		for(i=0;i<l/2;++i) {
			char temp=line[i];
			line[i]=line[l-i-1];
			line[l-i-1]=temp;
			}
		printf("результат второго потока: \n%s\n",line);
		sem_post(&invert_ready);
		}
	printf("второй поток заканчивает работу\n");
	return NULL;
	}
int main() {
	pthread_t input_thread,invert_thread;
	sem_init(&input_ready,0,0);
	sem_init(&invert_ready,0,1);
	int res=pthread_create(&input_thread,NULL,run_input,NULL);
	if(res!=0) {
		perror("первый поток не создан\n");
		exit(1);
		}
	res=pthread_create(&invert_thread,NULL,run_invert,NULL);
	if(res!=0) {
		perror("второй поток не создан\n");
		exit(1);
		}
	pthread_join(input_thread,NULL);
	pthread_join(invert_thread,NULL);
	sem_destroy(&input_ready);
	sem_destroy(&invert_ready);
	return 0;
	}

