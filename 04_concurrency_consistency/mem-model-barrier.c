#include <stdio.h>
#include <pthread.h>

int x = 0, y = 0;
int t1 = 0, t2 = 0;

void* T1(void* arg) {
    x = 1;
    __sync_synchronize();
    t1 = y;
    return NULL;
}

void* T2(void* arg) {
    y = 1;
    __sync_synchronize();
    t2 = x;
    return NULL;
}

int main() {
    int count_00 = 0, count_01 = 0, count_10 = 0, count_11 = 0;
    
    for (int i = 0; i < 100000; i++) { // 暴力跑十万次
        x = 0; y = 0;
        t1 = 0; t2 = 0;
        
        pthread_t th1, th2;
        pthread_create(&th1, NULL, T1, NULL);
        pthread_create(&th2, NULL, T2, NULL);
        pthread_join(th1, NULL);
        pthread_join(th2, NULL);
        
        if (t1 == 0 && t2 == 0) count_00++;
        else if (t1 == 0 && t2 == 1) count_01++;
        else if (t1 == 1 && t2 == 0) count_10++;
        else if (t1 == 1 && t2 == 1) count_11++;
    }
    
    printf("10万次测试结果：\n");
    printf("t1=0, t2=1: %d 次\n", count_01);
    printf("t1=1, t2=0: %d 次\n", count_10);
    printf("t1=1, t2=1: %d 次\n", count_11);
    printf("t1=0, t2=0: %d 次\n", count_00);
    
    return 0;
}