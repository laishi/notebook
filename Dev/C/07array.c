#include <stdio.h>

// 函数声明
void printIntArray(int arr[], int size);
void printString(char str[]);

int main() {
    // 数组的定义和使用
    int numbers[5] = {1, 2, 3, 4, 5};
    printf("Element at index 2: %d\n", numbers[2]);

    numbers[2] = 10;
    printf("Updated element at index 2: %d\n", numbers[2]);

    printf("Array elements: ");
    printIntArray(numbers, 5);

    // 字符串的定义和使用
    char greeting[6] = {'H', 'e', 'l', 'l', 'o', '\0'};
    printf("Greeting: ");
    printString(greeting);

    greeting[0] = 'J';
    printf("Updated greeting: ");
    printString(greeting);

    // 使用字符串库函数
    char name[] = "Alice";
    int length = 0;

    while (name[length] != '\0') {
        length++;
    }

    printf("Length of name: %d\n", length);

    return 0;
}

// 函数定义：打印整数数组
void printIntArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// 函数定义：打印字符串
void printString(char str[]) {
    printf("%s\n", str);
}

