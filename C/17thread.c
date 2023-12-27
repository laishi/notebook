#include <stdio.h>
#include <pthread.h>

// 任务1：打印奇数
void* printOddNumbers(void* arg) {
    for (int i = 1; i <= 10; i += 2) {
        printf("Odd: %d\n", i);
    }
    return NULL;
}

// 任务2：打印偶数
void* printEvenNumbers(void* arg) {
    for (int i = 2; i <= 10; i += 2) {
        printf("Even: %d\n", i);
    }
    return NULL;
}

int main() {
    // 创建两个线程
    pthread_t thread1, thread2;

    // 创建线程1，执行 printOddNumbers 函数
    if (pthread_create(&thread1, NULL, printOddNumbers, NULL) != 0) {
        fprintf(stderr, "Error creating thread 1\n");
        return 1;
    }

    // 创建线程2，执行 printEvenNumbers 函数
    if (pthread_create(&thread2, NULL, printEvenNumbers, NULL) != 0) {
        fprintf(stderr, "Error creating thread 2\n");
        return 1;
    }

    // 等待线程1和线程2完成
    if (pthread_join(thread1, NULL) != 0) {
        fprintf(stderr, "Error joining thread 1\n");
        return 1;
    }

    if (pthread_join(thread2, NULL) != 0) {
        fprintf(stderr, "Error joining thread 2\n");
        return 1;
    }

    return 0;
}

