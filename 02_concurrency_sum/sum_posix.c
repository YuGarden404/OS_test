#include <stdio.h>
#include <pthread.h> // 引入 POSIX 线程库

#define N 100000000
#define NUMBER_OF_THREADS 2

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

long sum = 0;

void *T_sum(void* nothing) {
    for (int i = 0; i < N; i++) {
        pthread_mutex_lock(&mutex);
        sum++;
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main() {
    pthread_t threads[NUMBER_OF_THREADS];
    
    for (int i = 0; i < NUMBER_OF_THREADS; i++) {
        pthread_create(&threads[i], NULL, T_sum, NULL);
    }
    
    for (int i = 0; i < NUMBER_OF_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    
    printf("sum = %ld\n", sum);
    printf("2*N = %ld\n", 2L * N);
    
    return 0;
}