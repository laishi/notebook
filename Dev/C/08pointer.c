#include <stdio.h>
#include <stdlib.h>

// 函数声明
void printDynamicArray(int *arr, int size);

int main() {
    int num = 42;
    int *ptr;  // 定义指针变量

    ptr = &num;  // 将指针指向变量的地址

    printf("Value of num: %d\n", num);
    printf("Address of num: %p\n", (void *)&num);
    printf("Value via pointer: %d\n", *ptr);
    printf("Address stored in pointer: %p\n", (void *)ptr);

    // 动态内存分配与释放
    int *dynamicArray;
    int size = 5;

    // 动态分配整数数组
    dynamicArray = (int *)malloc(size * sizeof(int));

    // 检查内存是否成功分配
    if (dynamicArray == NULL) {
        printf("Memory allocation failed.\n");
        return 1;  // 退出程序，返回错误码
    }

    // 初始化动态数组
    for (int i = 0; i < size; i++) {
        dynamicArray[i] = i * 2;
    }

    // 打印动态数组的值
    printf("Dynamic array elements: ");
    printDynamicArray(dynamicArray, size);

    // 释放动态分配的内存
    free(dynamicArray);

    return 0;
}

// 函数定义：打印动态数组
void printDynamicArray(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

