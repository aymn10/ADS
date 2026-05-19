/*
Design and implement a Threaded Binary Tree (TBT) supporting insertion and stackless tree traversal operations.
• Construct a Threaded Binary Tree 
• Implement insertion operation 
• Implement inorder traversal without recursion or stack 
• Implement preorder traversal without recursion or stack
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
    int lthread;
    int rthread;
} Node;

Node* root = NULL;

Node* createNode(int value) {
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->data = value;
    temp->left = NULL;
    temp->right = NULL;
    temp->lthread = 1;
    temp->rthread = 1;
    return temp;
}

void insert(int value) {
    Node* ptr = root;
    Node* parent = NULL;
    if (root == NULL) {
        root = createNode(value);
        return;
    }
    while (ptr != NULL) {
        if (value == ptr->data) {
            printf("Duplicate value not allowed\n");
            return;
        }
        parent = ptr;
        if (value < ptr->data) {
            if (ptr->lthread == 0) ptr = ptr->left;
            else break;
        }
        else {
            if (ptr->rthread == 0) ptr = ptr->right;
            else break;
        }
    }
    Node* newNode = createNode(value);
    if (value < parent->data) {
        newNode->left = parent->left;
        newNode->right = parent;
        parent->lthread = 0;
        parent->left = newNode;
    }
    else {
        newNode->left = parent;
        newNode->right = parent->right;
        parent->rthread = 0;
        parent->right = newNode;
    }
}

Node* inorderSuccessor(Node* ptr) {
    if (ptr->rthread == 1) return ptr->right;
    ptr = ptr->right;
    while (ptr->lthread == 0) ptr = ptr->left;
    return ptr;
}

void inorderTraversal() {
    if (root == NULL) {
        printf("Tree is empty\n");
        return;
    }
    Node* ptr = root;
    while (ptr->lthread == 0) ptr = ptr->left;
    printf("Inorder Traversal: ");
    while (ptr != NULL) {
        printf("%d ", ptr->data);
        ptr = inorderSuccessor(ptr);
    }
    printf("\n");
}

void preorderTraversal() {
    if (root == NULL) {
        printf("Tree is empty\n");
        return;
    }
    Node* ptr = root;
    printf("Preorder Traversal: ");
    while (ptr != NULL) {
        printf("%d ", ptr->data);
        if (ptr->lthread == 0) ptr = ptr->left;
        else if (ptr->rthread == 0) ptr = ptr->right;
        else {
            while (ptr != NULL && ptr->rthread == 1)
                ptr = ptr->right;

            if (ptr != NULL)
                ptr = ptr->right;
        }
    }
    printf("\n");
}

int main() {
    int value, choice;
    while (1)
    {
        printf("\n--- Threaded Binary Tree ---\n");
        printf("1. Insert Node\n");
        printf("2. Inorder Traversal\n");
        printf("3. Preorder Traversal\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
        case 1:
            printf("Enter value to insert: ");
            scanf("%d", &value);
            insert(value);
            break;
        case 2:
            inorderTraversal();
            break;
        case 3:
            preorderTraversal();
            break;
        case 4:
            return 0;
        default:
            printf("Invalid choice\n");
        }
    }
    return 0;
}

