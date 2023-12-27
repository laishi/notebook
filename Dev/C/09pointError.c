#include <stdio.h>
#include <stdlib.h>

// 函数声明
void printDynamicArray(int *arr, int size);

int main() {
    // 1. 野指针
    int *wildPtr;
    *wildPtr = 42;  // 野指针

    // 2. 内存泄漏
    int *memoryLeak = (int *)malloc(sizeof(int));
    // 没有释放内存

    // 3. 指针未初始化
    int *uninitializedPtr;
    *uninitializedPtr = 10;  // 未初始化的指针

    // 4. 指针越界
    int arr[5];
    int *outOfBoundsPtr = arr;
    outOfBoundsPtr[5] = 10;  // 越界访问

    // 5. 多重释放
    int *doubleFree = (int *)malloc(sizeof(int));
    free(doubleFree);
    free(doubleFree);  // 多重释放

    // 6. 使用栈上的指针
    int *stackPtr;
    {
        int localVar = 42;
        stackPtr = &localVar;
    }  // localVar 超出范围
    *stackPtr = 10;  // 使用栈上的指针

    // 正确的用法：动态内存分配与释放
    int *dynamicArray;
    int size = 5;

    dynamicArray = (int *)malloc(size * sizeof(int));

    if (dynamicArray == NULL) {
        printf("Memory allocation failed.\n");
        return 1;  // 退出程序，返回错误码
    }

    for (int i = 0; i < size; i++) {
        dynamicArray[i] = i * 2;
    }

    printf("Dynamic array elements: ");
    printDynamicArray(dynamicArray, size);

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

