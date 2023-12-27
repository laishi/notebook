#include <stdio.h>
#include <stdlib.h>

// 单链表节点结构
struct Node {
    int data;
    struct Node* next;
};

// 单链表的头节点
struct Node* head = NULL;

// 添加节点到单链表
void appendNode(int newData) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = newData;
    newNode->next = NULL;

    if (head == NULL) {
        head = newNode;
        return;
    }

    struct Node* current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;
}

// 栈的基本结构
#define MAX_SIZE 100

struct Stack {
    int arr[MAX_SIZE];
    int top;
};

// 初始化栈
void initializeStack(struct Stack* stack) {
    stack->top = -1;
}

// 判断栈是否为空
int isStackEmpty(struct Stack* stack) {
    return stack->top == -1;
}

// 入栈操作
void push(struct Stack* stack, int value) {
    if (stack->top == MAX_SIZE - 1) {
        printf("Stack overflow!\n");
        return;
    }
    stack->arr[++stack->top] = value;
}

// 出栈操作
int pop(struct Stack* stack) {
    if (isStackEmpty(stack)) {
        printf("Stack underflow!\n");
        return -1;
    }
    return stack->arr[stack->top--];
}

// 队列的基本结构
struct Queue {
    int arr[MAX_SIZE];
    int front, rear;
};

// 初始化队列
void initializeQueue(struct Queue* queue) {
    queue->front = -1;
    queue->rear = -1;
}

// 判断队列是否为空
int isQueueEmpty(struct Queue* queue) {
    return queue->front == -1;
}

// 入队操作
void enqueue(struct Queue* queue, int value) {
    if (queue->rear == MAX_SIZE - 1) {
        printf("Queue overflow!\n");
        return;
    }
    if (isQueueEmpty(queue)) {
        queue->front = 0;
    }
    queue->arr[++queue->rear] = value;
}

// 出队操作
int dequeue(struct Queue* queue) {
    if (isQueueEmpty(queue)) {
        printf("Queue underflow!\n");
        return -1;
    }
    int value = queue->arr[queue->front];
    if (queue->front == queue->rear) {
        // 队列中只有一个元素，重置队列
        initializeQueue(queue);
    } else {
        queue->front++;
    }
    return value;
}

int main() {
    // 单链表示例
    printf("Linked List Example:\n");
    appendNode(10);
    appendNode(20);
    appendNode(30);
    struct Node* current = head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n\n");

    // 栈示例
    printf("Stack Example:\n");
    struct Stack myStack;
    initializeStack(&myStack);
    push(&myStack, 10);
    push(&myStack, 20);
    push(&myStack, 30);
    while (!isStackEmpty(&myStack)) {
        printf("%d ", pop(&myStack));
    }
    printf("\n\n");

    // 队列示例
    printf("Queue Example:\n");
    struct Queue myQueue;
    initializeQueue(&myQueue);
    enqueue(&myQueue, 10);
    enqueue(&myQueue, 20);
    enqueue(&myQueue, 30);
    while (!isQueueEmpty(&myQueue)) {
        printf("%d ", dequeue(&myQueue));
    }
    printf("\n");

    return 0;
}

