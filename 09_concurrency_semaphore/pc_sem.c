#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t empty;
sem_t full;
sem_t mutex;

void P(sem_t *lk){
    sem_wait(lk);
}

void V(sem_t *lk){
    sem_post(lk);
}

void* producer(void* arg){
    while(1){
        P(&empty);
        P(&mutex);
        printf("(");
        V(&mutex);
        V(&full);
    }
    return NULL;
}

void* consumer(void* arg){
    while(1){
        P(&full);
        P(&mutex);
        printf(")");
        V(&mutex);
        V(&empty);
    }
    return NULL;
}

int main(){
    sem_init(&empty, 0, 5);
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1);
    pthread_t p,c;
    pthread_create(&p,NULL,producer,NULL);
    pthread_create(&c,NULL,consumer,NULL);

    pthread_join(p,NULL);
    pthread_join(c,NULL);
    return 0;
}