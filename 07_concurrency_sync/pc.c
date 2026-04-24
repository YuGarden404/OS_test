#include <stdio.h>
#include <pthread.h>

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t cv_p = PTHREAD_COND_INITIALIZER;
pthread_cond_t cv_c = PTHREAD_COND_INITIALIZER;

int n = 5;
int depth = 0;

void* producer(void* arg){
    while(1){
        pthread_mutex_lock(&lock);
        while(!(depth<n)){
            pthread_cond_wait(&cv_p,&lock);
        }
        depth++;
        printf("(");
        pthread_cond_signal(&cv_c);
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

void* consumer(void* arg){
    while(1){
        pthread_mutex_lock(&lock);
        while(!(depth>0)){
            pthread_cond_wait(&cv_c,&lock);
        }
        depth--;
        printf(")");
        pthread_cond_signal(&cv_p);
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

int main(){
    int P_NUM = 2; // 2个生产者
    int C_NUM = 2; // 2个消费者
    pthread_t p[P_NUM], c[C_NUM];
    
    for(int i=0; i<P_NUM; i++) pthread_create(&p[i], NULL, producer, NULL);
    for(int i=0; i<C_NUM; i++) pthread_create(&c[i], NULL, consumer, NULL);

    for(int i=0; i<P_NUM; i++) pthread_join(p[i], NULL);
    for(int i=0; i<C_NUM; i++) pthread_join(c[i], NULL);

    return 0;
}