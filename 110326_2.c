#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
pthread_mutex_t vilka[5];
void *filosof(void *arg) {
	int v1,v2,loc_id=*(int *)arg;
	if(loc_id%2) {
		v1=loc_id;
		v2=(loc_id+1)%5;
		}
	else {
		v1=(loc_id+1)%5;
		v2=loc_id;
		}
	while(1) {
		sleep(0.01);
		pthread_mutex_lock(&vilka[v1]);
		printf("философ %d взял вилку %d\n",loc_id,v1);
		pthread_mutex_lock(&vilka[v2]);
		printf("философ %d взял вилку %d\n",loc_id,v2);
		sleep(3);
		pthread_mutex_unlock(&vilka[v1]);
		pthread_mutex_unlock(&vilka[v2]);
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
	sleep(120);
    printf("прошло 120 секунд,выход из программы\n");
    exit(0);
	}
		
