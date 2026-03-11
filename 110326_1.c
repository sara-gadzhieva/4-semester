#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
pthread_mutex_t vilka[5];
void *filosof(void *arg) {
	int loc_id=*(int *)arg;
	while(1) {
		sleep(rand()%3+1);
		pthread_mutex_lock(&vilka[loc_id]);
		printf("философ %d взял вилку %d\n",loc_id,loc_id);
		///sleep(0.01);
		pthread_mutex_lock(&vilka[(loc_id+1)%5]);
		printf("философ %d взял вилку %d\n",loc_id,(loc_id+1)%5);
		sleep(3);
		pthread_mutex_unlock(&vilka[loc_id]);
		pthread_mutex_unlock(&vilka[(loc_id+1)%5]);
		printf("философ %d поел\n",loc_id);
		}
	return NULL;
	}
int main() {
	int i,id[5],res;
	pthread_t f_thread[5];
	for(i=0;i<5;i++) pthread_mutex_init(&vilka[i],NULL);
	for(i=0;i<5;i++) {
		id[i]=i;
		res=pthread_create(&f_thread[i],NULL,filosof,&id[i]);
		if(res!=0) {
			printf("поток не создан\n");
			exit(1);
			}
		}
	for(i=0;i<5;i++) pthread_join(f_thread[i],NULL);
	for(i=0;i<5;i++) pthread_mutex_destroy(&vilka[i]);
	return 0;
	}

