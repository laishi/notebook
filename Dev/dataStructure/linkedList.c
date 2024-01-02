#include <stdio.h>
#include <stdlib.h>



// 定义链表节点
struct Node {
    int da  // 存储数据
    struct Node* next;   // 指向下一个节点的指针
};

// 函数：在链表末尾添加节点
struct Node* appendNode(struct Node* head, int newData) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = newData;
    newNode->next = NULL;

    if (head == NULL) {
        return newNode; // 如果链表为空，新节点成为头节点
    }

    struct Node* current = head;
    while (current->next != NULL) {
        current = current->next;
    }

    current->next = newNode;
    return head;
}

// 函数：打印链表元素
void printList(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

// 函数：释放链表内存
void freeList(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        struct Node* next = current->next;
        free(current);
        current = next;
    }
}

int main() {
    struct Node* myList = NULL; // 初始化链表

    // 在链表末尾添加节点

    int count = 1000;
    for (int i = 0; i < count; ++i) {
       myList = appendNode(myList, i); 

    }

    // 打印链表元素
    printf("Linked List: ");
    printList(myList);

    // 释放链表内存
    freeList(myList);

    return 0;
}

