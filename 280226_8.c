#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#define n 64
void *thread_func(void *arg) {
	int loc_id;
	sleep(1);
	loc_id=*(int *)arg;
	for(int i=0;i<5;i++) {
		printf("thread %d is running i=%d\n",loc_id,i);
		sleep(1);		
		}
	return NULL;
	}
int main() {
	int result;
	pthread_t thread[n];
	for(int id=1;id<n+1;id++) {
		result=pthread_create(&thread[id-1],NULL,thread_func,&id);
		if(result!=0) {
			printf("error creating the %d thread\n",id);
			return EXIT_FAILURE;
			}
		else printf("%d thread creating\n",id);
		}
	for(int id=1;id<n+1;id++) {
		result=pthread_join(thread[id-1],NULL);
		if(result!=0) {
			fprintf(stderr,"error joining the %d thread\n",id);
			return EXIT_FAILURE;
			}
		else printf("%d thread joining\n",id);	
		}
	printf("done\n");
	return EXIT_SUCCESS;
	}
