#include <stdio.h>

// 函数：打印数组
void printArray(int arr[], int size) {
    for (int i = 0; i < size; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// 函数：求和
int sumArray(int arr[], int size) {
    int sum = 0;
    for (int i = 0; i < size; ++i) {
        sum += arr[i];
    }
    return sum;
}

// 函数：查找数组中的最大值和最小值
void findMinMax(int arr[], int size, int *max, int *min) {
    *max = arr[0];
    *min = arr[0];

    for (int i = 1; i < size; ++i) {
        if (arr[i] > *max) {
            *max = arr[i];
        }

        if (arr[i] < *min) {
            *min = arr[i];
        }
    }
}

// 函数：逆序数组
void reverseArray(int arr[], int size) {
    for (int i = 0, j = size - 1; i < j; ++i, --j) {
        // 交换元素
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

// 函数：判断数组是否有重复元素
int hasDuplicate(int arr[], int size) {
    for (int i = 0; i < size - 1; ++i) {
        for (int j = i + 1; j < size; ++j) {
            if (arr[i] == arr[j]) {
                return 1; // 有重复元素
            }
        }
    }
    return 0; // 没有重复元素
}

int main() {
    // 声明并初始化一个整型数组
    int myArray[] = {1, 2, 3, 4, 5};

    // 数组元素的访问
    int value = myArray[2];
    printf("Value at index 2: %d\n", value);

    // 数组的遍历
    printf("Array elements: ");
    printArray(myArray, 5);

    // 数组的求和
    int sum = sumArray(myArray, 5);
    printf("Sum of array elements: %d\n", sum);

    // 查找数组中的最大值和最小值
    int max, min;
    findMinMax(myArray, 5, &max, &min);
    printf("Maximum value: %d\n", max);
    printf("Minimum value: %d\n", min);

    // 数组的逆序
    reverseArray(myArray, 5);
    printf("Reversed array: ");
    printArray(myArray, 5);

    // 判断数组是否有重复元素
    if (hasDuplicate(myArray, 5)) {
        printf("Array has duplicate elements.\n");
    } else {
        printf("Array does not have duplicate elements.\n");
    }

    return 0;
}

