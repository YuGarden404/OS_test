#include <stdio.h>
#include <pthread.h>

#define SIZE 5
pthread_mutex_t forks[SIZE];
int id[SIZE];

void* eating(void* arg){
    int * val = (int*)arg;
    while(1){
        int left = *val;
        int right = (*val + 1)%SIZE;
        if(left>right){
            pthread_mutex_lock(&forks[right]);
            pthread_mutex_lock(&forks[left]);
            printf("Philosopher %d is eating...\n", *val);
            pthread_mutex_unlock(&forks[left]);
            pthread_mutex_unlock(&forks[right]);
        }else{
            pthread_mutex_lock(&forks[left]);
            pthread_mutex_lock(&forks[right]);
            printf("Philosopher %d is eating...\n", *val);
            pthread_mutex_unlock(&forks[right]);
            pthread_mutex_unlock(&forks[left]);
        }
    }
    return NULL;
}

int main(){
    pthread_t philosophers[SIZE];
    for(int i = 0;i<SIZE;i++){
        id[i]=i;
        pthread_mutex_init(&forks[i], NULL);
        pthread_create(&philosophers[i],NULL,eating,&id[i]);
    }
    
    for(int i = 0;i<SIZE;i++){
        pthread_join(philosophers[i],NULL);
    }
    return 0;
}