// ============================================
// 1. SINGLY LINKED LIST
// ============================================
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node *createNode(int data) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;
    return node;
}

// insert at head
void prepend(Node **head, int data) {
    Node *node = createNode(data);
    node->next = *head;
    *head = node;
}

// insert at tail
void append(Node **head, int data) {
    Node *node = createNode(data);
    if (*head == NULL) { *head = node; return; }
    Node *temp = *head;
    while (temp->next != NULL) temp = temp->next;
    temp->next = node;
}

// delete by value
void deleteNode(Node **head, int data) {
    if (*head == NULL) return;
    if ((*head)->data == data) {
        Node *temp = *head;
        *head = (*head)->next;
        free(temp);
        return;
    }
    Node *temp = *head;
    while (temp->next && temp->next->data != data)
        temp = temp->next;
    if (temp->next) {
        Node *del = temp->next;
        temp->next = del->next;
        free(del);
    }
}

void printList(Node *head) {
    while (head) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

void freeList(Node **head) {
    Node *temp;
    while (*head) {
        temp = *head;
        *head = (*head)->next;
        free(temp);
    }
}

// ============================================
// 2. STACK (LIFO) - using linked list
// ============================================

typedef struct Stack {
    int data;
    struct Stack *next;
} Stack;

void push(Stack **top, int data) {
    Stack *node = (Stack *)malloc(sizeof(Stack));
    node->data = data;
    node->next = *top;
    *top = node;
}

int pop(Stack **top) {
    if (*top == NULL) { printf("stack underflow\n"); return -1; }
    Stack *temp = *top;
    int val = temp->data;
    *top = (*top)->next;
    free(temp);
    return val;
}

int peek(Stack *top) {
    if (top == NULL) { printf("stack empty\n"); return -1; }
    return top->data;
}

void printStack(Stack *top) {
    while (top) {
        printf("%d -> ", top->data);
        top = top->next;
    }
    printf("NULL\n");
}

// ============================================
// 3. QUEUE (FIFO) - using linked list
// ============================================

typedef struct QNode {
    int data;
    struct QNode *next;
} QNode;

typedef struct Queue {
    QNode *front;
    QNode *rear;
} Queue;

Queue *createQueue() {
    Queue *q = (Queue *)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    return q;
}

void enqueue(Queue *q, int data) {
    QNode *node = (QNode *)malloc(sizeof(QNode));
    node->data = data;
    node->next = NULL;
    if (q->rear == NULL) {
        q->front = q->rear = node;
        return;
    }
    q->rear->next = node;
    q->rear = node;
}

int dequeue(Queue *q) {
    if (q->front == NULL) { printf("queue empty\n"); return -1; }
    QNode *temp = q->front;
    int val = temp->data;
    q->front = q->front->next;
    if (q->front == NULL) q->rear = NULL;
    free(temp);
    return val;
}

void printQueue(Queue *q) {
    QNode *temp = q->front;
    while (temp) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

// ============================================
// 4. BINARY SEARCH TREE
// ============================================

typedef struct BSTNode {
    int data;
    struct BSTNode *left;
    struct BSTNode *right;
} BSTNode;

BSTNode *insertBST(BSTNode *root, int data) {
    if (root == NULL) {
        BSTNode *node = (BSTNode *)malloc(sizeof(BSTNode));
        node->data = data;
        node->left = node->right = NULL;
        return node;
    }
    if (data < root->data)
        root->left = insertBST(root->left, data);
    else if (data > root->data)
        root->right = insertBST(root->right, data);
    return root;
}

// left -> root -> right (sorted order)
void inorder(BSTNode *root) {
    if (root == NULL) return;
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}

int searchBST(BSTNode *root, int data) {
    if (root == NULL) return 0;
    if (root->data == data) return 1;
    if (data < root->data) return searchBST(root->left, data);
    return searchBST(root->right, data);
}

// ============================================
// MAIN - demo all structures
// ============================================

int main() {
    // --- linked list ---
    printf("=== LINKED LIST ===\n");
    Node *head = NULL;
    append(&head, 1);
    append(&head, 2);
    append(&head, 3);
    prepend(&head, 0);
    printList(head);           // 0 -> 1 -> 2 -> 3 -> NULL
    deleteNode(&head, 2);
    printList(head);           // 0 -> 1 -> 3 -> NULL
    freeList(&head);

    // --- stack ---
    printf("\n=== STACK (LIFO) ===\n");
    Stack *top = NULL;
    push(&top, 10);
    push(&top, 20);
    push(&top, 30);
    printStack(top);           // 30 -> 20 -> 10 -> NULL
    printf("peek: %d\n", peek(top));       // 30
    printf("pop:  %d\n", pop(&top));       // 30
    printf("pop:  %d\n", pop(&top));       // 20
    printStack(top);           // 10 -> NULL

    // --- queue ---
    printf("\n=== QUEUE (FIFO) ===\n");
    Queue *q = createQueue();
    enqueue(q, 10);
    enqueue(q, 20);
    enqueue(q, 30);
    printQueue(q);             // 10 -> 20 -> 30 -> NULL
    printf("dequeue: %d\n", dequeue(q));   // 10
    printf("dequeue: %d\n", dequeue(q));   // 20
    printQueue(q);             // 30 -> NULL
    free(q);

    // --- BST ---
    printf("\n=== BINARY SEARCH TREE ===\n");
    BSTNode *root = NULL;
    root = insertBST(root, 50);
    root = insertBST(root, 30);
    root = insertBST(root, 70);
    root = insertBST(root, 20);
    root = insertBST(root, 40);
    printf("inorder (sorted): ");
    inorder(root);             // 20 30 40 50 70
    printf("\n");
    printf("search 40: %s\n", searchBST(root, 40) ? "found" : "not found");
    printf("search 99: %s\n", searchBST(root, 99) ? "found" : "not found");

    return 0;
}


// linked list  -- dynamic memory, pointers, traversal
// stack        -- LIFO, push/pop, call stack in real CPUs
// queue        -- FIFO, front/rear pointers, task scheduling
// BST          -- recursion, left < root < right invariant
