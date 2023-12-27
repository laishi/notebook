#include <stdio.h>

// 函数声明
void exampleFunction();

int main() {
    int num = 10;

    // 条件语句
    if (num > 0) {
        printf("%d is positive.\n", num);
    }

    if (num % 2 == 0) {
        printf("%d is even.\n", num);
    } else {
        printf("%d is odd.\n", num);
    }

    if (num < 0) {
        printf("%d is negative.\n", num);
    } else if (num == 0) {
        printf("%d is zero.\n", num);
    } else {
        printf("%d is positive.\n", num);
    }

    // switch语句
    int choice = 2;
    switch (choice) {
        case 1:
            printf("You chose option 1.\n");
            break;
        case 2:
            printf("You chose option 2.\n");
            break;
        case 3:
            printf("You chose option 3.\n");
            break;
        default:
            printf("Invalid choice.\n");
    }

    // for循环
    for (int i = 0; i < 5; i++) {
        printf("%d ", i);
    }
    printf("\n");

    // while循环
    int k = 0;
    while (k < 5) {
        printf("%d ", k);
        k++;
    }
    printf("\n");

    // do-while循环
    int j = 0;
    do {
        printf("%d ", j);
        j++;
    } while (j < 5);
    printf("\n");

    // break和continue语句
    for (int i = 0; i < 10; i++) {
        if (i == 5) {
            break;
        }
        printf("%d ", i);
    }
    printf("\n");

    for (int j = 0; j < 5; j++) {
        if (j == 2) {
            continue;
        }
        printf("%d ", j);
    }
    printf("\n");

    // goto语句
    int m = 0;
    start:
    printf("%d ", m);
    m++;
    if (m < 5) {
        goto start;
    }
    printf("\n");

    // 调用函数
    exampleFunction();

    return 0;
}

// 函数定义
void exampleFunction() {
    printf("This is an example function.\n");
}

