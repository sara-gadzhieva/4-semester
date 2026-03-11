#include <pthread.h>
#include <stdio.h>
#include <stdbool.h>
#include <semaphore.h>
#include <unistd.h>
int plan,ispech,prodan;
sem_t sem_empty,sem_full;
pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
void *f_bulochniki(void *arg) {
	int num=*(int *)arg;
	while(true) {
		sem_wait(&sem_empty); ///уменьшаем количество свободных мест на прилавке
		pthread_mutex_lock(&mutex);
		if(ispech>=plan) {
			pthread_mutex_unlock(&mutex);
			sem_post(&sem_empty); ///увеличиваем количество свободных обратно
			break;
			}
		ispech++;
		printf("булочник %d испек булку, испечено %d/%d\n",num,ispech,plan);
		pthread_mutex_unlock(&mutex);
		sem_post(&sem_full); ///увеличивает количество занятых мест
		sleep(3);
		}
	return NULL;
	}
void *f_pokupateli(void *arg) {
	int num=*(int *)arg;
	while(true) {
		sem_wait(&sem_full); ///уменьшаем количество занятых мест
		pthread_mutex_lock(&mutex);
		if(prodan>=plan) {
			pthread_mutex_unlock(&mutex);
			sem_post(&sem_full);
			break;
			}
		prodan++;
		printf("покупатель %d купил булку, продано %d/%d\n",num,prodan,plan);
		pthread_mutex_unlock(&mutex);
		sem_post(&sem_empty); ///увеличивает количество свободных
		sleep(1);
		}
	return NULL;
	}
int main() {
	int n1,n2,mesta;
	printf("введите число булочников: ");   
	scanf("%d",&n1);
	printf("введите число покупателей: ");  
	scanf("%d",&n2);
	printf("введите план производства: ");            
	scanf("%d",&plan);
	printf("введите количество мест на прилавке: ");        
	scanf("%d",&mesta);
	sem_init(&sem_empty,0,mesta);
	sem_init(&sem_full,0,0);
	pthread_t bulochniki[n1],pokupateli[n2];
	int id_bulochniki[n1],id_pokupateli[n2];
	for(int i=0;i<n1;i++) {
		id_bulochniki[i]=i+1;
		pthread_create(&bulochniki[i],NULL,f_bulochniki,&id_bulochniki[i]);
		}
	for(int i=0;i<n2;i++) {
		id_pokupateli[i]=i+1;
		pthread_create(&pokupateli[i],NULL,f_pokupateli,&id_pokupateli[i]);
		}
	for(int i=0;i<n1;i++) pthread_join(bulochniki[i],NULL);
	for(int i=0;i<n2;i++) sem_post(&sem_full);
	for(int i=0;i<n2;i++) pthread_join(pokupateli[i],NULL);
	pthread_mutex_destroy(&mutex);
	sem_destroy(&sem_empty);
	sem_destroy(&sem_full);
	printf("испечено %d булок, продано %d булок\n",ispech,prodan);
	return 0;
	}
