#include <stdio.h>
#include <pthread.h> // 引入 POSIX 线程库

#define N 100000000
#define NUMBER_OF_THREADS 2

// 这是一个多线程共享的全局变量
long sum = 0;

typedef struct {
    int ticket; // 记录当前发到了第几号（取号机）
    int turn;   // 记录当前叫到了第几号（大屏幕）
} lock_t;

lock_t my_ticket_lock = {0, 0}; // 初始化都是 0

void my_lock(){
    int my_turn = __sync_fetch_and_add(&my_ticket_lock.ticket, 1);
    while(my_turn!=my_ticket_lock.turn);
}

void my_unlock(){
    __sync_synchronize();//屏障
    //__sync_fetch_and_add(&my_ticket_lock.turn,1);
    my_ticket_lock.turn++;
}

// 线程要执行的函数：疯狂对 sum 进行加 1 操作
void *T_sum(void* nothing) {
    for (int i = 0; i < N; i++) {
        my_lock();
        sum++;
        my_unlock();
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