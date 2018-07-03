//Compile: gcc test.c -o test -lpthread 
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <limits.h>

int value;
pthread_mutex_t mutex;
pthread_cond_t cond;

void init(void);
void destroy(void);

void* thread_function(void* args) {
    int i;
    while(1){
	pthread_mutex_lock(&mutex);
	if(value == 66) {
	    printf("good luck\n");
	} else {
	    pthread_cond_wait(&cond, &mutex);
	    printf("hello, value:%d\n", value);
	}
	pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main(void){
    value = 0;
    init();
    pthread_t  mythread;
    if(pthread_create(&mythread, NULL, thread_function, NULL)){
	printf("error creating thread.\n");
	abort();
    }
    int j;
    for(j=0; j<INT_MAX; j++){
	pthread_mutex_lock(&mutex);
	value = value + 1;
	pthread_mutex_unlock(&mutex);
	pthread_cond_signal(&cond);
    }
    if(pthread_join(mythread, NULL)){
	printf("error creating thread.\n");
	abort();
    }
    printf("value:%d\n", value);
    destroy();
    exit(0);
}

void init() {
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);
}

void destroy(void){
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);
}
