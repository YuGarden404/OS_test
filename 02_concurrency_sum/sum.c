#include <stdio.h>
#include <pthread.h> // 引入 POSIX 线程库

#define N 100000000
#define NUMBER_OF_THREADS 2

// 这是一个多线程共享的全局变量
long sum = 0;

// 线程要执行的函数：疯狂对 sum 进行加 1 操作
void *T_sum(void* nothing) {
    for (int i = 0; i < N; i++) {
        sum++;
    }
    return NULL; // 相当于课件里的 pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUMBER_OF_THREADS];
    
    // 1. 创建 2 个线程，它们会同时去执行 T_sum 函数
    for (int i = 0; i < NUMBER_OF_THREADS; i++) {
        pthread_create(&threads[i], NULL, T_sum, NULL);
    }
    
    // 2. 等待这 2 个线程执行完毕
    for (int i = 0; i < NUMBER_OF_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    
    // 3. 打印最终结果
    printf("sum = %ld\n", sum);
    printf("2*N = %ld\n", 2L * N);
    
    return 0;
}