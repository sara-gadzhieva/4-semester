#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#define n 3
void *thread_func(void *arg) {
	int loc_id=*(int *)arg;
	for(int i=0;i<3;i++) {
		printf("thread %d is running i=%d\n",loc_id,i);
		sleep(1);
		}
	return NULL;
	}
int main() {
	int id[n],result,i;
	pthread_t thread[n];
	for(int i=0;i<n;i++) {
		id[i]=i+1;
		result=pthread_create(&thread[i],NULL,thread_func,&id[i]);
		if(result!=0) {
			fprintf(stderr,"error creating the %d thread\n",id[i]);
			return EXIT_FAILURE;
			}
		else printf("%d thread creating\n",id[i]);
		}
	for(int i=0;i<n;i++) {
		result=pthread_join(thread[i],NULL);
		if(result!=0) {
			fprintf(stderr,"error joining the %d thread\n",id[i]);
			return EXIT_FAILURE;
			}
		else printf("%d thread joining\n",id[i]);	
		}
	printf("done\n");
	return EXIT_SUCCESS;
	}
