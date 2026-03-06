#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>
sem_t sem;
pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
void *thread_func(void *arg) {
	int i,j,loc_id;
	sleep(1);
	loc_id=*(int *)arg;
	sem_post(&sem);
	for(j=0;j<5;j++) {
		pthread_mutex_lock(&mutex);
		for(i=0;i<3;i++) {
			printf("поток %d, стр. %d\n",loc_id,i+1);
			sleep(rand()%2);
			}
		printf("~~~~~~~~~~~~~~~\n");
		pthread_mutex_unlock(&mutex);
		sleep(rand()%10);		
		}
	return NULL;
	}
int main() {
	int id,result;
	pthread_t thread[3];
	sem_init(&sem,0,0);
	for(id=1;id<4;id++) {
		result=pthread_create(&thread[id-1],NULL,thread_func,&id);
		if(result!=0) {
			printf("error creating the %d thread\n",id);
			return EXIT_FAILURE;
			}
		sem_wait(&sem);
		}
	for(id=1;id<4;id++) {
		result=pthread_join(thread[id-1],NULL);
		if(result!=0) {
			fprintf(stderr,"error joining the %d thread\n",id);
			return EXIT_FAILURE;
			}
		else printf("%d thread joining\n",id);	
		}
	sem_destroy(&sem);
	pthread_mutex_destroy(&mutex);
	printf("done\n");
	return EXIT_SUCCESS;	
	}
