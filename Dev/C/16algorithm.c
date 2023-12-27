#include <stdio.h>
#include <stdlib.h>

// 冒泡排序
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // 交换元素
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// 插入排序
void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        // 将比 key 大的元素向后移动
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }

        // 插入 key 到合适位置
        arr[j + 1] = key;
    }
}

// 线性查找
int linearSearch(int arr[], int n, int target) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == target) {
            return i;  // 找到目标元素，返回索引
        }
    }
    return -1;  // 目标元素未找到
}

// 二分查找
int binarySearch(int arr[], int low, int high, int target) {
    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (arr[mid] == target) {
            return mid;  // 找到目标元素，返回索引
        }

        if (arr[mid] < target) {
            low = mid + 1;  // 在右侧继续查找
        } else {
            high = mid - 1;  // 在左侧继续查找
        }
    }

    return -1;  // 目标元素未找到
}

int main() {
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arr) / sizeof(arr[0]);
    int target = 22;

    // 冒泡排序
    bubbleSort(arr, n);

    printf("Sorted array (Bubble Sort): ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // 插入排序
    insertionSort(arr, n);

    printf("Sorted array (Insertion Sort): ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // 线性查找
    int linearResult = linearSearch(arr, n, target);
    if (linearResult != -1) {
        printf("Element %d found at index %d (Linear Search).\n", target, linearResult);
    } else {
        printf("Element %d not found in the array (Linear Search).\n", target);
    }

    // 二分查找 (注意：二分查找要求有序数组)
    int binaryResult = binarySearch(arr, 0, n - 1, target);
    if (binaryResult != -1) {
        printf("Element %d found at index %d (Binary Search).\n", target, binaryResult);
    } else {
        printf("Element %d not found in the array (Binary Search).\n", target);
    }

    return 0;
}

