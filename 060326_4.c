#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <semaphore.h>
#include <unistd.h>
int n1,n2,plan,mesta;
int ispech=0;
int prodan=0;
sem_t sem_empty;
sem_t sem_full;
pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
void *f_bulochniki(void *arg) {
	int num=*(int *)arg;
	while(true) {
		sem_wait(&sem_empty);
		pthread_mutex_lock(&mutex);
		if(ispech>=plan) {
			pthread_mutex_unlock(&mutex);
			sem_post(&sem_empty);
			break;
			}
		ispech++;
		printf("булочник %d положил булку (испечено: %d/%d)\n",num,ispech,plan);
		pthread_mutex_unlock(&mutex);
		sem_post(&sem_full);
		sleep(1);
		}
	return NULL;
	}
void *f_pokupateli(void *arg) {
	int num=*(int *)arg;
	while(true) {
		sem_wait(&sem_full);
		pthread_mutex_lock(&mutex);
		if(prodan>=plan) {
			pthread_mutex_unlock(&mutex);
			break;
			}
		prodan++;
		printf("покупатель %d купил булку (продано: %d/%d)\n",num,prodan,plan);
		pthread_mutex_unlock(&mutex);
		sem_post(&sem_empty);
		sleep(2);
		}
	return NULL;
	}
int main() {
	printf("количество булочников: ");   
	scanf("%d",&n1);
	printf("количество покупателей: ");  
	scanf("%d",&n2);
	printf("план выпечки: ");            
	scanf("%d",&plan);
	printf("мест на прилавке: ");        
	scanf("%d",&mesta);
	pthread_t bulochniki[n1],pokupateli[n2];
	int ids_b[n1],ids_p[n2];
	sem_init(&sem_empty,0,mesta);
	sem_init(&sem_full,0,0);
	for(int i=0;i<n1;i++) {
		ids_b[i]=i+1;
		pthread_create(&bulochniki[i],NULL,f_bulochniki,&ids_b[i]);
		}
	for(int i=0;i<n2;i++) {
		ids_p[i]=i+1;
		pthread_create(&pokupateli[i],NULL,f_pokupateli,&ids_p[i]);
		}
	for(int i=0;i<n1;i++) pthread_join(bulochniki[i],NULL);
	for(int i=0;i<n2;i++) sem_post(&sem_full);
	for(int i=0;i<n2;i++) pthread_join(pokupateli[i],NULL);
	pthread_mutex_destroy(&mutex);
	sem_destroy(&sem_empty);
	sem_destroy(&sem_full);
	printf("\nиспечено: %d, продано: %d\n",ispech,prodan);
	return 0;
	}
