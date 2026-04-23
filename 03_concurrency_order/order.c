#include <stdbool.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#define NUMBER_OF_THREADS 2

bool volatile done = false;

void* func1(void* arg){
    while(!done){
        if(done){
            printf("Thread 1 finished!\n");
            break;
        }
    }
    return NULL;
}

void* func2(void* arg){
    sleep(1);
    done = true;
    return NULL;
}

int main(){
    pthread_t threads[NUMBER_OF_THREADS];
    
    pthread_create(&threads[0],NULL,func1,NULL);
    pthread_create(&threads[1],NULL,func2,NULL);

    for(int i = 0;i<NUMBER_OF_THREADS;i++){
        pthread_join(threads[i],NULL);
    }

    return 0;
}